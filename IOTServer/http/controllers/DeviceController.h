#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DeviceController : public drogon::HttpController<DeviceController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(DeviceController::newDevice, "/api/device/new", Put, "LoginFilter", "AdminFilter");
        ADD_METHOD_TO(DeviceController::deleteDevice, "/api/device/delete", Delete, "LoginFilter", "AdminFilter");
        ADD_METHOD_TO(DeviceController::getAllDevice, "/api/device/all", Get, "LoginFilter");
        ADD_METHOD_TO(DeviceController::getDevice, "/api/device", Get, "LoginFilter");

    METHOD_LIST_END

    /**
     * Create New Device To Device Table
     * @param req
     * @param callback
     */
    void newDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Delete Device From Device Table
     * @param req
     * @param callback
     */
    void deleteDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Fetch All Device
     * @param req
     * @param callback
     */
    void getAllDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
