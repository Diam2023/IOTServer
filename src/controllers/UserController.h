#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

/**
 * For User Action Control
 */
class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(UserController::login, "/user/login", Post);
        ADD_METHOD_TO(UserController::logout, "/user/logout", Delete, "LoginFilter");
        ADD_METHOD_TO(UserController::getInfo, "/user/info", Get, "LoginFilter");

    METHOD_LIST_END

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void getInfo(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
