//
// Created by diam on 24-1-13.
//

#include "common.h"
#include "UserApi.h"

#include <string>
#include <string_view>

#include <drogon/HttpAppFramework.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::IOTServerDB;
using namespace std;

namespace api {
    std::future<std::string> UserApi::login(const std::string &key, const std::string &pwd) {

        auto dbClientPtr = app().getFastDbClient();

        // ORM:
        Mapper<Users> mp(dbClientPtr);

        std::shared_ptr<std::promise<std::string>> prom = std::make_shared<std::promise<std::string>>();

        try {
            auto user = mp.findOne((Criteria(Users::Cols::_user_name, CompareOperator::EQ, key) ||
                                    Criteria(Users::Cols::_user_id, CompareOperator::EQ, key)) &&
                                   Criteria(Users::Cols::_user_password, CompareOperator::EQ, pwd));
            // Successful find

            // generator token
            auto token = utils::getUuid();

            // Push to Redis
            auto redisClientPtr = app().getFastRedisClient();
            redisClientPtr->execCommandSync([prom, token](const RedisResult &r) {
                LOG_INFO << "Token: " << token << " Res: " << r.getStringForDisplaying();
                prom->set_value(token);
            }, "set %s%s %s", TOKEN_PREFIX, token, user.getUserId());
        } catch (const RedisException &e) {
            LOG_WARN << e.what();
            prom->set_exception(std::current_exception());
        } catch (const DrogonDbException &e) {
            prom->set_exception(std::current_exception());
        } catch (const std::exception &e) {
            LOG_WARN << e.what();
            prom->set_exception(std::current_exception());
        }
        return prom->get_future();
    }

    std::future<bool> UserApi::logout(const string &token) {
        auto redisClientPtr = app().getFastRedisClient();

        std::shared_ptr<std::promise<bool>> prom = std::make_shared<std::promise<bool>>();

        redisClientPtr->execCommandAsync([prom, token](const RedisResult &r) {
            if (r.type() == RedisResultType::kNil) {
                // throw RedisException(RedisErrorCode::kNone, "Not found");
                prom->set_value(false);
            } else {
                prom->set_value(true);
            }
        }, [prom](const RedisException &e) {
            prom->set_exception(current_exception());
        }, "get %s%s", TOKEN_PREFIX, token);

        return prom->get_future();
    }
} // api