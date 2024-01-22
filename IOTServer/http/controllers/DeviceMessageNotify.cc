#include "DeviceMessageNotify.h"
#include "Tools.h"

#include "SubscribeMap.h"
#include "Device.h"
#include "Topic.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;

struct Subscriber {
    std::string uid;
    drogon::SubscriberID sid{};
};

void DeviceMessageNotify::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                           const WebSocketMessageType &type) {
    // Ignore
}

void
DeviceMessageNotify::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    Subscriber subscriber;
    subscriber.uid = req->getHeader("uid");
    subscriber.sid = DeviceMessageNotify::getNotifyService().subscribe(subscriber.uid,
                                             [wsConnPtr](const std::string &topic,
                                                         const mqtt::MqttData &data) {
                                                 Json::Value value;
                                                 value["topic"] = data.first.name().toStdString();
                                                 value["json"] = data.second.toStyledString();
                                                 wsConnPtr->send(value.toStyledString());
                                             });
    wsConnPtr->setContext(std::make_shared<Subscriber>(subscriber));
}

void DeviceMessageNotify::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    auto &s = wsConnPtr->getContextRef<Subscriber>();
    DeviceMessageNotify::getNotifyService().unsubscribe(s.uid, s.sid);
}

void DeviceMessageNotifyHandler::handler(const mqtt::MqttData &data) {

    auto &service = DeviceMessageNotify::getNotifyService();

    auto result = getDeviceSerialNumberAndSubTopic(data.first.name().toStdString());
    if (!result.first.empty()) {

        auto deviceProm = std::make_shared<std::promise<drogon_model::iot_server::Device>>();
        drogon::app().getLoop()->runInLoop([deviceProm, result]() {
            auto dbClientPtr = drogon::app().getDbClient();
            Mapper<drogon_model::iot_server::Device> deviceMapper(dbClientPtr);
            deviceMapper.findOne(
                    Criteria(drogon_model::iot_server::Device::Cols::_device_sn, CompareOperator::EQ, result.first),
                    [deviceProm](const drogon_model::iot_server::Device &r) {
                        deviceProm->set_value(r);
                    }, [deviceProm](const auto &e) {
                        deviceProm->set_exception(std::current_exception());
                    });
        });

        uint32_t deviceId;
        drogon_model::iot_server::Device device;
        try {
            device = deviceProm->get_future().get();
            deviceId = *device.getDeviceId();
        } catch (const DrogonDbException &e) {
            // Not Found
            return;
        }


        auto topicProm = std::make_shared<std::promise<drogon_model::iot_server::Topic>>();
        drogon::app().getLoop()->runInLoop([topicProm, result, deviceId]() {
            auto dbClientPtr = drogon::app().getDbClient();
            Mapper<drogon_model::iot_server::Topic> topicMapper(dbClientPtr);
            topicMapper.findOne(
                    Criteria(drogon_model::iot_server::Topic::Cols::_target_device_id, CompareOperator::EQ, deviceId)
                    && Criteria(drogon_model::iot_server::Topic::Cols::_topic_name, CompareOperator::EQ, result.second),
                    [topicProm](const drogon_model::iot_server::Topic &r) {
                        topicProm->set_value(r);
                    }, [topicProm](const auto &e) {
                        topicProm->set_exception(std::current_exception());
                    });
        });

        uint32_t topicId;
        drogon_model::iot_server::Topic topic;
        try {
            topic = topicProm->get_future().get();
            topicId = *topic.getTopicId();
        } catch (const DrogonDbException &e) {
            // Not Found
            return;
        }
        auto userIdListProm = std::make_shared<std::promise<std::vector<uint32_t>>>();

        drogon::app().getLoop()->runInLoop([userIdListProm, deviceId, topicId]() {
            auto dbClientPtr = drogon::app().getDbClient();
            Mapper<drogon_model::iot_server::SubscribeMap> subsMapper(dbClientPtr);
            subsMapper.findBy(
                    Criteria(drogon_model::iot_server::SubscribeMap::Cols::_target_device_id, CompareOperator::EQ,
                             deviceId)
                    && Criteria(drogon_model::iot_server::SubscribeMap::Cols::_target_topic_id, CompareOperator::EQ,
                                topicId),
                    [userIdListProm](const auto &r) {
                        std::vector<uint32_t> uidList;
                        for (const drogon_model::iot_server::SubscribeMap &subs: r) {
                            uidList.push_back(*subs.getTargetUserId());
                        }
                        userIdListProm->set_value(uidList);
                    }, [userIdListProm](const auto &e) {
                        userIdListProm->set_exception(std::current_exception());
                    });
        });

        std::vector<uint32_t> userIdList;
        try {
            userIdList = userIdListProm->get_future().get();
        } catch (const DrogonDbException &e) {
            // Not Found
            return;
        }

        if (userIdList.empty()) {
            // NON Data Tp Send
            return;
        }

        // Publish
        for (auto uid: userIdList) {
            service.publish(std::to_string(uid), data);
        }

    }
}
