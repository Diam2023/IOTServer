#include "DeviceController.h"

#include "Device.h"
#include "User.h"

#include "UserApi.h"
#include "DeviceApi.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::iot_server;
using namespace std;

// Add definition of your processing function here
void DeviceController::newDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto userId = req->getHeader("uid");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (!*jsonBody || jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }
        try {
            // New Device
            api::DeviceApi::addDevice(Device(*jsonBody)).get();

            resCode = k200OK;
        } catch (const DrogonDbException &e) {
            resCode = k400BadRequest;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void
DeviceController::deleteDevice(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto userId = req->getHeader("uid");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }

        auto deviceSn = (*jsonBody)["device_sn"];
        if (deviceSn.empty() ||
            (deviceSn.type() != Json::ValueType::stringValue)) {
            resCode = k400BadRequest;
            break;
        }
        try {
            // New Device
            auto res = api::DeviceApi::removeDevice(deviceSn.asString()).get();
            if (res) {
                resCode = k200OK;
            } else {
                resCode = k404NotFound;
            }
        } catch (const DrogonDbException &e) {
            resCode = k400BadRequest;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void DeviceController::getAllDevice(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    auto future = api::DeviceApi::listDevices();

    Json::Value jsonValue;
    Json::Value devicesJson;

    HttpStatusCode resCode;

    try {
        auto devices = future.get();
        // TODO Need To Filter If user Permission lower than device
        for (auto &device: *devices) {
            jsonValue.append(device.toJson());
        }

        resCode = k200OK;
    } catch (const UnexpectedRows &e) {
        resCode = k404NotFound;
    } catch (const std::exception &e) {
        resCode = k500InternalServerError;
    }

    auto resp = resCode == k200OK ? HttpResponse::newHttpJsonResponse(jsonValue) : HttpResponse::newHttpResponse();
    resp->setStatusCode(resCode);
    callback(resp);
}

void DeviceController::getDevice(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    auto userId = req->getHeader("uid");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (!*jsonBody || jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }

        auto deviceSn = (*jsonBody)["device_sn"];
        if (deviceSn.empty() ||
            (deviceSn.type() != Json::ValueType::stringValue)) {
            resCode = k400BadRequest;
            break;
        }
        try {
            // get Device
            auto device = api::DeviceApi::getDevice(deviceSn.asString()).get();
            resJson = device.toJson();
            resCode = k200OK;
        } catch (const DrogonDbException &e) {
            resCode = k400BadRequest;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}
