#include "UserController.h"

#include "Users.h"
#include <json/value.h>
#include "UserApi.h"

using namespace drogon::orm;
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

        if (keyField) {
            resCode = k203NonAuthoritativeInformation;
            break;
        }

        if (pwdField) {
            resCode = k203NonAuthoritativeInformation;
            break;
        }

        try {
            auto future = api::UserApi::login(keyField.asString(), pwdField.asString());
            auto result = future.get();
            resJson["token"] = result;
            resCode = k200OK;
        } catch (const std::exception &e) {
            resCode = k401Unauthorized;
        }
    } while (false);

    auto resp = HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void UserController::logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Direct Call logout


}

void UserController::getInfo(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

}
