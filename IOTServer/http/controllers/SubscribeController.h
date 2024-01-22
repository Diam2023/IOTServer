#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SubscribeController : public drogon::HttpController<SubscribeController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(SubscribeController::newSubscribe, "/api/subscribe/new", Put, "LoginFilter", "AdminFilter");
        ADD_METHOD_TO(SubscribeController::deleteSubscribe, "/api/subscribe/delete", Delete, "LoginFilter",
                      "AdminFilter");
        ADD_METHOD_TO(SubscribeController::getAllSubscribe, "/api/subscribe/all", Get, "LoginFilter");

    METHOD_LIST_END

    /**
     * Create New Topic To Topic Table
     * @param req
     * @param callback
     */
    void newSubscribe(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Delete Topic From Topic Table
     * @param req
     * @param callback
     */
    void deleteSubscribe(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Get All Topic For Device
     * @param req
     * @param callback
     */
    void getAllSubscribe(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
