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

}
