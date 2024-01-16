#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

/**
 * For User Action Control
 */
class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(UserController::newUser, "/user/register", Put);
        ADD_METHOD_TO(UserController::login, "/user/login", Post);
        ADD_METHOD_TO(UserController::logout, "/user/logout", Delete, "LoginFilter");
        ADD_METHOD_TO(UserController::getInfo, "/user/info", Get, "LoginFilter");
        // Delete User admin permission

        ADD_METHOD_TO(UserController::addDevice, "/user/device/add", Put, "LoginFilter");
        ADD_METHOD_TO(UserController::removeDevice, "/user/device/remove", Delete, "LoginFilter");

        ADD_METHOD_TO(UserController::getAllDevice, "/user/device/getAll", Get, "LoginFilter");
        ADD_METHOD_TO(UserController::getDeviceInfo, "/user/device/get", Get, "LoginFilter");

        ADD_METHOD_TO(UserController::addTopic, "/user/topic/add", Put, "LoginFilter");
        ADD_METHOD_TO(UserController::removeTopic, "/user/topic/remove", Delete, "LoginFilter");

    METHOD_LIST_END

    /**
     * Register a new user
     * @param req request
     * @param callback response callback
     */
    void newUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Http login
     * @param req request
     * @param callback response callback
     */
    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Http logout
     * @param req request
     * @param callback response callback
     */
    void logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Http Get user info
     * @param req request
     * @param callback response callback
     */
    void getInfo(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);


    /**
     * Add Device To User Subscribe
     * @param req request
     * @param callback response callback
     */
    void addDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);


    /**
     * Remove Device From User Subscribe
     * @param req
     * @param callback
     */
    void removeDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Get All Subscribed device
     * @param req
     * @param callback
     */
    void getAllDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * subscribe device topic
     * @param req
     * @param callback
     */
    void addTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * unsubscribe device topic
     * @param req
     * @param callback
     */
    void removeTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
