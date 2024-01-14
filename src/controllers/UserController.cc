#include "UserController.h"

#include "Users.h"
#include <json/value.h>
#include "common.h"
#include "UserApi.h"

using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::IOTServerDB;

void UserController::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Get Fast DB

    // Request body

    Json::Value resJson;
    auto resCode = kUnknown;

    do {
        auto reqJson = req->getJsonObject();

        if (reqJson->isNull()) {
            resCode = k203NonAuthoritativeInformation;
            break;
        }

        auto keyField = (*reqJson)["key"];
        auto pwdField = (*reqJson)["pwd"];

        if (keyField.empty() || pwdField.empty()) {
            resCode = k203NonAuthoritativeInformation;
            break;
        }

        try {
            auto future = api::UserApi::login(keyField.asString(), pwdField.asString());
            auto result = future.get();
            resJson["token"] = result;
            resCode = k200OK;
        } catch (const std::exception &e) {
            LOG_WARN << e.what();
            resCode = k401Unauthorized;
        }
    } while (false);

    auto resp = HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void UserController::logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Direct Call logout
    // Token Has verified by LoginFilter

    // Call Logout Api

    auto resCode = kUnknown;
    auto token = req->getHeader("token");

    try {

        auto future = api::UserApi::logout(token);
        auto res = future.get();

        if (res) {
            resCode = k200OK;
        } else {
            resCode = k417ExpectationFailed;
        }

    } catch (const std::exception &e) {
        LOG_WARN << e.what();
        resCode = k503ServiceUnavailable;
    }

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(resCode);
    callback(resp);
}

void UserController::getInfo(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Get userid first

    const std::string_view token = req->getHeader("token");

    auto redisClientPtr = app().getRedisClient();

    Json::Value resJson;
    auto resCode = kUnknown;

    std::shared_ptr<std::promise<std::string>> prom = std::make_shared<std::promise<std::string>>();


    redisClientPtr->execCommandAsync([prom](const RedisResult &res) {
        if (res.type() != RedisResultType::kString) {
            throw RedisException(RedisErrorCode::kNone, "Not found");
        } else {
            prom->set_value(res.asString());
        }
    }, [prom](const RedisException &e) {
        prom->set_exception(std::current_exception());
    }, "get %s%s", TOKEN_PREFIX, token);


    try {
        auto resId = prom->get_future().get();

        auto dbClientPtr = app().getDbClient();
        // ORM:
        Mapper<Users> mp(dbClientPtr);

        // find user with id
        auto future = mp.findFutureOne(Criteria(Users::Cols::_user_id, CompareOperator::EQ, resId));
        auto resUser = future.get();

        // Mask pwd
        resUser.setUserPassword("");
        resJson["user"] = resUser.toJson();
        resCode = k200OK;


    } catch (const std::exception &e) {
        // TODO Restructure reqCode
        LOG_WARN << e.what();
        resJson["err"] = e.what();
        resCode = k400BadRequest;
    }

    // response
    auto resp = HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void UserController::newUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto reqJson = req->getJsonObject();
    auto userPtr = std::make_shared<Users>(*reqJson);

    auto dbClientPtr = app().getDbClient();
    // ORM:
    Mapper<Users> mp(dbClientPtr);

    auto resCode = k200OK;

    // Check permission
    // Initialize to 0
    userPtr->setUserPermissionId(DEFAULT_PERMISSION_ID);

    try {
        // insert
        auto future = mp.insertFuture(*userPtr);
        auto res = future.get();
    } catch (const std::exception &e) {
        LOG_WARN << e.what();
        resCode = k500InternalServerError;
    }

    // response
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(resCode);
    callback(resp);
}
