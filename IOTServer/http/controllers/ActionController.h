#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ActionController : public drogon::HttpController<ActionController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(ActionController::newAction, "/api/action/new", Put, "LoginFilter");
        ADD_METHOD_TO(ActionController::deleteAction, "/api/action/delete", Delete, "LoginFilter");
        ADD_METHOD_TO(ActionController::getAllAction, "/api/action/all", Get, "LoginFilter");

        ADD_METHOD_TO(ActionController::callAction, "/api/action/call", Put, "LoginFilter");

    METHOD_LIST_END

    /**
     * Create New Device To Action
     * @param req
     * @param callback
     */
    void newAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Delete Device From Action
     * @param req
     * @param callback
     */
    void deleteAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Fetch All Device Action For user
     * @param req
     * @param callback
     */
    void getAllAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void callAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
