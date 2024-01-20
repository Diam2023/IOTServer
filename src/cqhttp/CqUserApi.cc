//
// Created by diam on 24-1-20.
//

#include "CqUserApi.h"

#include <memory>
#include <tuple>
#include "UserApi.h"
#include <drogon/drogon.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;
using namespace std;

// 推送到EvenLoop
//登入时调用UserApi登入，获取Token之后新建 QK:qq号 Token的模式
//然后添加集合QB:qq号 bot号 到Redis
//最后添加集合UQ:uid qq号
//然后把登入结果发回
//
//中间类CqCommandExcutor
//
//
//Mqtt消息推送实现 以下逻辑 推送到EvenLoop 全异步接口
//处理类找到订阅的所有uid 然后在Redis内通过UQ找，循环两个集合 获取bot号，然后查找一个在线(Pool)的bot号
//构造要发送的数据<ConnPtr, Json::Value>发送到CqMessagePublisher 避免线程锁定
//发送数据到QQ


namespace cq {

    std::future<std::string> CqUserApi::getLoginInfo(const std::string &qqId) {

        // Use IO Loop
        auto prom = std::make_shared<std::promise<std::string>>();
        drogon::app().getLoop()->queueInLoop([prom, qqId]() {
            auto redisClientPtr = app().getRedisClient();
            redisClientPtr->execCommandAsync([prom](const RedisResult &r) {
                if (r.type() != RedisResultType::kString) {
                    prom->set_value("");
                } else {
                    prom->set_value(r.asString());
                }
            }, [prom](const RedisException &e) {
                LOG_WARN << e.what();
                prom->set_exception(std::current_exception());
            }, "get %s%s", QK_PREFIX, qqId.c_str());
        });

        return prom->get_future();
    }

    std::future<std::string> CqUserApi::login(const std::string &botId, const std::string &qqId, const std::string &usr,
                                              const std::string &pwd) {
        auto prom = std::make_shared<std::promise<std::string>>();
        drogon::app().getLoop()->queueInLoop([prom, usr, pwd, qqId, botId]() {
            try {
                auto token = api::UserApi::login(usr, pwd).get();
                if (token.empty()) {
                    prom->set_value(token);
                } else {
                    // first Successful
                    auto uid = api::UserApi::getUserId(token).get();

                    auto redisClientPtr = app().getRedisClient();
                    redisClientPtr->execCommandAsync([](const RedisResult &r) {
                    }, [prom, token](const RedisException &e) {
                        LOG_WARN << e.what();
//                        prom->set_exception(std::current_exception());
                    }, "set %s%s %u", QK_PREFIX, qqId.c_str(), token.c_str());

                    redisClientPtr->execCommandAsync([](const RedisResult &r) {
                    }, [prom, token](const RedisException &e) {
                        LOG_WARN << e.what();
//                        prom->set_exception(std::current_exception());
                    }, "set %s%s %u", QB_PREFIX, qqId.c_str(), botId.c_str());

                    redisClientPtr->execCommandAsync([](const RedisResult &r) {
                    }, [prom, token](const RedisException &e) {
                        LOG_WARN << e.what();
//                        prom->set_exception(std::current_exception());
                    }, "set %s%s %u", UQ_PREFIX, uid.c_str(), qqId.c_str());
                    prom->set_value(token);
                }
            } catch (const std::exception &e) {
                prom->set_exception(std::make_exception_ptr(e));
            }

        });

        return prom->get_future();
    }

    std::future<bool> CqUserApi::logout(const string &qqId) {
        auto prom = std::make_shared<std::promise<bool>>();

        auto token = getLoginInfo(qqId).get();

        if (token.empty()) {
            prom->set_value(false);
            return prom->get_future();
        }

        try {
            api::UserApi::logout(token).get();
        } catch (const RedisException &e) {
            // TODO Handle This
        }

        auto redisClientPtr = app().getRedisClient();

        redisClientPtr->execCommandAsync([prom](const RedisResult &r) {
            if ((r.type() != RedisResultType::kInteger) || (r.asInteger() != 1)) {
                prom->set_exception(std::make_exception_ptr(RedisException(RedisErrorCode::kNone, "Unknown Err")));
            } else {
                prom->set_value(true);
            }
        }, [prom](const RedisException &e) {
            prom->set_exception(current_exception());
        }, "del %s%s", QK_PREFIX, qqId.c_str());

        return prom->get_future();
    }
} // cq