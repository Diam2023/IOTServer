#include "SubscribeController.h"

#include "User.h"
#include <json/value.h>
#include "Topic.h"

using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;

// Add definition of your processing function here
void SubscribeController::newTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
//    HttpStatusCode resCode;
//    Json::Value resJson;
//
//    do {
//        auto jsonBody = req->getJsonObject();
//        if (jsonBody->empty()) {
//            resCode = k400BadRequest;
//            break;
//        }
//
//
//        try {
//            // New Device
//            api::TopicApi::newTopic(Topic(*jsonBody)).get();
//
//            resCode = k200OK;
//        } catch (const DrogonDbException &e) {
//            resCode = k400BadRequest;
//        } catch (const std::exception &e) {
//            resCode = k500InternalServerError;
//        }
//    } while (false);
//
//    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
//    resp->setStatusCode(resCode);
//    callback(resp);

}

void SubscribeController::deleteTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
//    HttpStatusCode resCode;
//    Json::Value resJson;
//
//    do {
//        auto jsonBody = req->getJsonObject();
//        if (jsonBody->empty()) {
//            resCode = k400BadRequest;
//            break;
//        }
//
//        auto topicId = (*jsonBody)["topic_id"];
//        if (topicId.empty() || !topicId.isNumeric()) {
//            resCode = k400BadRequest;
//            break;
//        }
//
//        try {
//            // New Device
//            api::TopicApi::deleteTopic(topicId.asUInt()).get();
//
//            resCode = k200OK;
//        } catch (const DrogonDbException &e) {
//            resCode = k400BadRequest;
//        } catch (const std::exception &e) {
//            resCode = k500InternalServerError;
//        }
//    } while (false);
//
//    auto resp = resJson.empty() ? HttpResponse::newHttpResponse() : HttpResponse::newHttpJsonResponse(resJson);
//    resp->setStatusCode(resCode);
//    callback(resp);
}

void SubscribeController::getAllTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
//    auto dbClientPtr = app().getDbClient();
//    Mapper<Topic> topicMapper(dbClientPtr);
//
//    Json::Value jsonDeviceId;
//
//    if (req->contentType() == ContentType::CT_APPLICATION_JSON) {
//        auto reqJsonObj = req->getJsonObject();
//        jsonDeviceId = (*reqJsonObj)["device_id"];
//    }
//
//    auto future = jsonDeviceId.empty() ? topicMapper.findFutureAll() : topicMapper.findFutureBy(
//            Criteria(Topic::Cols::_target_device_id, CompareOperator::EQ, jsonDeviceId.asString()));
//
//    Json::Value jsonValue;
//    Json::Value topicsJson;
//
//    HttpStatusCode resCode;
//
//    try {
//        auto topics = future.get();
//        // TODO Need To Filter If user Permission lower than device
//        for (auto &topic: topics) {
//            topicsJson.append(topic.toJson());
//        }
//
//        if (!jsonDeviceId.empty()) {
//            jsonValue["device_id"] = jsonDeviceId;
//        }
//
//        jsonValue["topics"] = topicsJson;
//        resCode = k200OK;
//    } catch (const UnexpectedRows &e) {
//        resCode = k404NotFound;
//    } catch (const std::exception &e) {
//        resCode = k500InternalServerError;
//    }
//
//    auto resp = resCode == k200OK ? HttpResponse::newHttpJsonResponse(jsonValue) : HttpResponse::newHttpResponse();
//    resp->setStatusCode(resCode);
//    callback(resp);
}
