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
        if (jsonBody->empty()) {
            resCode = k204NoContent;
            break;
        }
        try {
            // New Device
            api::DeviceApi::newDevice(Device(*jsonBody)).get();

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
            resCode = k406NotAcceptable;
            break;
        }

        auto deviceId = (*jsonBody)["device_id"];
        if (deviceId.empty() ||
            ((deviceId.type() != Json::ValueType::uintValue) && (deviceId.type() != Json::ValueType::intValue))) {
            resCode = k406NotAcceptable;
            break;
        }
        try {
            // New Device
            auto res = api::DeviceApi::deleteDevice(deviceId.asUInt64()).get();
            if (res) {
                resCode = k200OK;
            } else {
                resCode = k204NoContent;
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

    auto dbClientPtr = app().getDbClient();
    Mapper<Device> deviceMapper(dbClientPtr);
    auto future = deviceMapper.findFutureAll();

    Json::Value jsonValue;
    Json::Value devicesJson;

    HttpStatusCode resCode;

    try {
        auto devices = future.get();
        for (auto &device: devices) {
            devicesJson.append(device.toJson());
        }

        jsonValue["devices"] = devicesJson;
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
