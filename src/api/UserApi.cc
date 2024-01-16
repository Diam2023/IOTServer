//
// Created by diam on 24-1-13.
//

#include "common.h"

#include <drogon/utils/Utilities.h>
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>

#include <string>
#include <string_view>

#include "UserApi.h"
#include "Device.h"
#include "SubscribeMap.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;
using namespace std;

namespace api {
    std::future<std::string> UserApi::login(const std::string &key, const std::string &pwd) {

        auto dbClientPtr = app().getDbClient();

        // ORM:
        Mapper<User> mp(dbClientPtr);

        std::shared_ptr<std::promise<std::string>> prom = std::make_shared<std::promise<std::string>>();

        try {
            auto user = mp.findOne((Criteria(User::Cols::_user_name, CompareOperator::EQ, key) ||
                                    Criteria(User::Cols::_user_id, CompareOperator::EQ, key)) &&
                                   Criteria(User::Cols::_user_password, CompareOperator::EQ, pwd));
            // Successful find

            // generator token
            std::string token = drogon::utils::getUuid(true);

            // Push to Redis
            auto redisClientPtr = app().getRedisClient();
            redisClientPtr->execCommandAsync([prom, token](const RedisResult &r) {
                prom->set_value(token);
            }, [prom, token](const RedisException &e) {
                LOG_WARN << e.what();
                prom->set_exception(std::current_exception());
            }, "set %s%s %u", TOKEN_PREFIX, token.c_str(), *user.getUserId());
        } catch (const RedisException &e) {
            LOG_WARN << e.what();
            prom->set_exception(std::current_exception());
        } catch (const DrogonDbException &e) {
            LOG_WARN << "D DB E";
            prom->set_exception(std::current_exception());
        } catch (const std::exception &e) {
            LOG_WARN << e.what();
            prom->set_exception(std::current_exception());
        }
        return prom->get_future();
    }

    std::future<bool> UserApi::logout(const string &token) {
        auto redisClientPtr = app().getRedisClient();

        std::shared_ptr<std::promise<bool>> prom = std::make_shared<std::promise<bool>>();

        redisClientPtr->execCommandAsync([prom](const RedisResult &r) {
            if ((r.type() != RedisResultType::kInteger) && (r.asInteger() != 1)) {
                prom->set_value(false);
            } else {
                prom->set_value(true);
            }
        }, [prom](const RedisException &e) {
            prom->set_exception(current_exception());
        }, "del %s%s", TOKEN_PREFIX, token.c_str());

        return prom->get_future();
    }

    std::future<std::string> UserApi::getUserId(const string &token) {
        // Promise
        std::shared_ptr<std::promise<std::string>> prom = std::make_shared<std::promise<std::string>>();
        // Get Redis ptr
        // TODO Check Ptr is null
        auto redisClientPtr = app().getRedisClient();
        // Run command
        redisClientPtr->execCommandAsync([prom](const RedisResult &r) {
            if (r.type() != RedisResultType::kString) {
                prom->set_exception(std::make_exception_ptr(RedisException(RedisErrorCode::kNone, "Not found")));
            } else {
                prom->set_value(r.asString());
            }
        }, [prom](const RedisException &e) {
            prom->set_exception(current_exception());
        }, "get %s%s", TOKEN_PREFIX, token.c_str());

        return prom->get_future();
    }

    std::future<bool> UserApi::addDevice(const string &token, const string &deviceId) {
        auto prom = std::make_shared<std::promise<bool>>();

        try {
            auto userId = api::UserApi::getUserId(token).get();
            auto dbClientPtr = app().getDbClient();

            Json::Value subscribeMapJson;
            subscribeMapJson["target_user_id"] = userId;
            subscribeMapJson["target_device_id"] = deviceId;
            // init to zero
            // all topic
            // subscribeMapJson["target_topic_id"] = ;

            Mapper<SubscribeMap> subscribeMapMapper(dbClientPtr);

            subscribeMapMapper.insertFuture(SubscribeMap(subscribeMapJson)).get();
            prom->set_value(true);

        } catch (const UnexpectedRows &e) {
            prom->set_exception(make_exception_ptr(e));
        }

        return prom->get_future();
    }

    std::future<bool> UserApi::removeDevice(const string &token, const string &deviceId) {
        auto prom = std::make_shared<std::promise<bool>>();

        try {
            auto userId = api::UserApi::getUserId(token).get();
            auto dbClientPtr = app().getDbClient();

            Mapper<SubscribeMap> subscribeMapMapper(dbClientPtr);

            auto deletedSize = subscribeMapMapper.deleteFutureBy(
                    Criteria(SubscribeMap::Cols::_target_user_id, CompareOperator::EQ, userId)).get();
            if (deletedSize > 0) {
                prom->set_value(true);
            } else {
                prom->set_value(false);
            }
        } catch (const UnexpectedRows &e) {
            prom->set_exception(make_exception_ptr(e));
        } catch (const std::exception &e) {
            LOG_WARN << e.what();
            prom->set_exception(make_exception_ptr(e));
        }
        return prom->get_future();
    }

    std::future<uint32_t> UserApi::getUserPermissionLevel(const string &token) {

        // Promise
        std::shared_ptr<std::promise<uint32_t>> prom = std::make_shared<std::promise<uint32_t>>();
        // Get Redis ptr

        try {
            auto userId = api::UserApi::getUserId(token).get();
            auto dbClientPtr = app().getDbClient();

            Mapper<User> userMapper(dbClientPtr);
            auto user = userMapper.findFutureOne(Criteria(User::Cols::_user_id, CompareOperator::EQ, userId)).get();
            prom->set_value(*user.getUserPermissionLevel());
        } catch (const UnexpectedRows &e) {
            prom->set_exception(make_exception_ptr(e));
        } catch (const RedisException &e) {
            // Need Login
            prom->set_exception(make_exception_ptr(e));
        } catch (const std::exception &e) {
            prom->set_exception(make_exception_ptr(e));
        }

        return prom->get_future();
    }

    std::future<std::vector<drogon_model::iot_server::Device>> UserApi::getAllSubscribedDevice(const string &userId) {
        auto prom = std::make_shared<std::promise<std::vector<drogon_model::iot_server::Device>>>();
        auto dbClientPtr = app().getDbClient();
        Mapper<SubscribeMap> subScribeMapper(dbClientPtr);
        Mapper<Device> deviceMapper(dbClientPtr);

        std::vector<drogon_model::iot_server::Device> devices;

        try {

            auto topics = subScribeMapper.orderBy(SubscribeMap::Cols::_target_device_id).findFutureBy(
                    Criteria(SubscribeMap::Cols::_target_user_id, CompareOperator::EQ, userId)).get();

            // remove replace item
            vector<SubscribeMap> noRepTopics;
            std::copy(topics.begin(), topics.end(), noRepTopics.begin());
            noRepTopics.erase(unique(noRepTopics.begin(), noRepTopics.end(),
                                     [](const SubscribeMap &fir, const SubscribeMap &sec) -> bool {
                                         return fir.getTargetDeviceId() == sec.getTargetDeviceId();
                                     }), noRepTopics.end());

            for (auto &topic: noRepTopics) {
                auto res = deviceMapper.findFutureOne(
                        Criteria(Device::Cols::_device_id, CompareOperator::EQ, *topic.getTargetDeviceId())).get();
                devices.push_back(res);
            }

            prom->set_value(devices);

        } catch (const UnexpectedRows &e) {
            prom->set_exception(std::make_exception_ptr(e));
        } catch (const DrogonDbException &e) {
            prom->set_exception(std::make_exception_ptr(e));
        } catch (const std::exception &e) {
            prom->set_exception(current_exception());
        }


        return prom->get_future();
    }

    std::future<std::vector<drogon_model::iot_server::Topic>>
    UserApi::getSubscribedDeviceAllTopics(const string &userId, const string &deviceId) {
        auto prom = std::make_shared<std::promise<std::vector<drogon_model::iot_server::Topic>>>();
        auto dbClientPtr = app().getDbClient();
        Mapper<SubscribeMap> subScribeMapper(dbClientPtr);
        Mapper<Topic> topicMapper(dbClientPtr);

        std::vector<drogon_model::iot_server::Topic> topics;

        try {
            auto subscribeMapList = subScribeMapper.findFutureBy(
                    Criteria(SubscribeMap::Cols::_target_user_id, CompareOperator::EQ, userId) &&
                    Criteria(SubscribeMap::Cols::_target_device_id, CompareOperator::EQ, deviceId)).get();

            for (auto &subscribeMap: subscribeMapList) {
                auto topic = topicMapper.findFutureOne(
                        Criteria(Topic::Cols::_topic_id, CompareOperator::EQ, *subscribeMap.getTargetTopicId())).get();
                topics.push_back(topic);
            }

            prom->set_value(topics);
        } catch (const UnexpectedRows &e) {
            prom->set_exception(std::make_exception_ptr(DataException("Non Topic")));
        } catch (const DrogonDbException &e) {
            prom->set_exception(current_exception());
        } catch (const std::exception &e) {
            prom->set_exception(current_exception());
        }

        return prom->get_future();
    }
} // api