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

            resJson["msg"] = "id or pwd error";
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
    auto token = req->getHeader("Authorization");

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

    auto token = req->getHeader("Authorization");
    auto uid = req->getHeader("uid");

    Json::Value resJson;
    auto resCode = kUnknown;
    if (token.empty()) {
        resCode = k203NonAuthoritativeInformation;
        auto resp = HttpResponse::newHttpJsonResponse(resJson);

    }

    try {
        if (uid.empty()) {
            // verify token out of date!
            uid = api::UserApi::getUserId(token).get();
        }

        auto dbClientPtr = app().getDbClient();
        // ORM:
        Mapper<Users> mp(dbClientPtr);

        // find user with id
        auto resUser = mp.findFutureOne(
                Criteria(Users::Cols::_user_id, CompareOperator::EQ, uid)).get();

        // Mask pwd
        resUser.setUserPassword("");
        resJson["user"] = resUser.toJson();
        resCode = k200OK;
    } catch (const RedisException &e) {
        resCode = k401Unauthorized;
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
