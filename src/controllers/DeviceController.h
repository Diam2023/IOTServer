#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DeviceController : public drogon::HttpController<DeviceController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(DeviceController::newDevice, "/device/new", Put, "LoginFilter");
        ADD_METHOD_TO(DeviceController::deleteDevice, "/device/delete", Delete, "LoginFilter");


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
};
