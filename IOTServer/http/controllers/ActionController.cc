#include "ActionController.h"


#include "ActionApi.h"
#include "UserDeviceActionMap.h"

void ActionController::newAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (!*jsonBody || jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }
        auto actionName = (*jsonBody)["action_name"];
        auto deviceSn = (*jsonBody)["device_sn"];
        auto topicName = (*jsonBody)["topic_name"];
        auto actionJson = (*jsonBody)["action_json"];
        try {

            // New action
            api::ActionApi::addAction(token, actionName.asString(), deviceSn.asString(), topicName.asString(),
                                      actionJson.toStyledString()).get();

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
ActionController::deleteAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    do {
        auto jsonBody = req->getJsonObject();
        if (!*jsonBody || jsonBody->empty()) {
            resCode = k400BadRequest;
            break;
        }
        auto actionName = (*jsonBody)["action_name"];
        try {

            // un Subs
            api::ActionApi::removeAction(token, actionName.asString());

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
ActionController::getAllAction(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto &token = req->getHeader("Authorization");

    HttpStatusCode resCode;
    Json::Value resJson;

    try {
        // List Subs
        auto deviceTopicActionList = api::ActionApi::listAction(token).get();

        if (!deviceTopicActionList->empty()) {
            // Sort it by device id
            std::sort(deviceTopicActionList->begin(), deviceTopicActionList->end(), [](auto fir, auto sec) -> bool {
                const drogon_model::iot_server::Device &firDevice = std::get<0>(fir);
                const drogon_model::iot_server::Device &secDevice = std::get<0>(fir);
                if (*firDevice.getDeviceId() == *secDevice.getDeviceId()) {
                    const drogon_model::iot_server::Topic &firTopic = std::get<1>(fir);
                    const drogon_model::iot_server::Topic &secTopic = std::get<1>(fir);

                    return *firTopic.getTopicId() < *secTopic.getTopicId();
                } else {
                    return *firDevice.getDeviceId() < *secDevice.getDeviceId();
                }
            });
            for (const auto &deviceTopicsActions: *deviceTopicActionList) {
                resJson["devices"].append(std::get<0>(deviceTopicsActions).toJson());
                resJson["topics"].append(std::get<1>(deviceTopicsActions).toJson());
                resJson["actions"].append(std::get<2>(deviceTopicsActions).toJson());
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
