#include "AliasController.h"

#include "AliasApi.h"
#include "Device.h"
#include "UserDeviceAliasMap.h"

// Add definition of your processing function here
void AliasController::newAlias(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (!*jsonBody || jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }
        auto deviceSn = (*jsonBody)["device_sn"];
        auto alias = (*jsonBody)["alias"];
        try {

            // New Alias
            api::AliasApi::addAlias(token, deviceSn.asString(), alias.asString()).get();

            resCode = k200OK;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void AliasController::deleteAlias(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }
        auto alias = (*jsonBody)["alias"];
        try {

            // New Alias
            api::AliasApi::removeAlias(token, alias.asString()).get();

            resCode = k200OK;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void AliasController::getUserDeviceAlias(const HttpRequestPtr &req,
                                         std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        try {

            // New Alias
            auto deviceAliasList = api::AliasApi::listAlias(token).get();

            if (!deviceAliasList->empty()) {
                // Sort it by device id
                std::sort(deviceAliasList->begin(), deviceAliasList->end(), [](auto fir, auto sec) -> bool {
                    const drogon_model::iot_server::Device &firDevice = fir.first;
                    const drogon_model::iot_server::Device &secDevice = sec.first;
                    return *firDevice.getDeviceId() < *secDevice.getDeviceId();
                });
                for (const auto &deviceAlias: *deviceAliasList) {
                    resJson["devices"].append(deviceAlias.first.toJson());
                    resJson["aliases"].append(deviceAlias.second.toJson());
                }
            }
            resCode = k200OK;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}
