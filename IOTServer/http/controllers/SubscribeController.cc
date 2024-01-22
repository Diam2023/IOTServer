#include "SubscribeController.h"

#include "User.h"
#include <json/value.h>
#include "Topic.h"
#include "SubscribeMap.h"
#include "Device.h"
#include "SubscribeApi.h"

using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;

void
SubscribeController::newSubscribe(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
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
        auto topicName = (*jsonBody)["topic"];
        try {

            // New Subs
            api::SubscribeApi::subscribeDeviceTopic(token, deviceSn.asString(), topicName.asString()).get();

            resCode = k200OK;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void
SubscribeController::deleteSubscribe(const HttpRequestPtr &req,
                                     std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }
        auto deviceSn = (*jsonBody)["device_sn"];
        auto topicName = (*jsonBody)["topic"];
        try {

            // un Subs
            api::SubscribeApi::unsubscribeDeviceTopic(token, deviceSn.asString(), topicName.asString()).get();

            resCode = k200OK;
        } catch (const std::exception &e) {
            resCode = k500InternalServerError;
        }
    } while (false);

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}

void
SubscribeController::getAllSubscribe(const HttpRequestPtr &req,
                                     std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    try {
        // List Subs
        auto deviceTopicList = api::SubscribeApi::listAllSubscribe(token).get();

        if (!deviceTopicList->empty()) {
            // Sort it by device id
            std::sort(deviceTopicList->begin(), deviceTopicList->end(), [](auto fir, auto sec) -> bool {
                const drogon_model::iot_server::Device &firDevice = fir.first;
                const drogon_model::iot_server::Device &secDevice = sec.first;
                return *firDevice.getDeviceId() < *secDevice.getDeviceId();
            });
            for (const auto &deviceTopics: *deviceTopicList) {
                resJson["devices"].append(deviceTopics.first.toJson());
                resJson["topics"].append(deviceTopics.second.toJson());
            }
        }
        resCode = k200OK;
    } catch (const std::exception &e) {
        resCode = k500InternalServerError;
    }

    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
    resp->setStatusCode(resCode);
    callback(resp);
}
