#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AliasController : public drogon::HttpController<AliasController>
{
  public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(AliasController::newAlias, "/api/alias/new", Put, "LoginFilter");
        ADD_METHOD_TO(AliasController::deleteAlias, "/api/alias/delete", Delete, "LoginFilter");
        ADD_METHOD_TO(AliasController::getUserDeviceAlias, "/api/alias/all", Get, "LoginFilter");

    METHOD_LIST_END

    /**
     * Create New Device To Device Table
     * @param req
     * @param callback
     */
    void newAlias(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Delete Device From Device Table
     * @param req
     * @param callback
     */
    void deleteAlias(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Fetch All Device Alias For user
     * @param req
     * @param callback
     */
    void getUserDeviceAlias(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
