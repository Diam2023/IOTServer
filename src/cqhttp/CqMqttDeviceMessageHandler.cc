//
// Created by diam on 24-1-19.
//

#include "CqMqttDeviceMessageHandler.h"
#include "Tools.h"

cq::CqMqttDeviceMessageHandler::CqMqttDeviceMessageHandler() = default;

void cq::CqMqttDeviceMessageHandler::handler(const mqtt::MqttData &data) {
    // TODO TEST Data
    auto result = getDeviceSerialNumberAndSubTopic(data.first.name().toStdString());
    if (!result.first.empty()) {

        LOG_INFO << "Received SN: " << result.first << " Sub Topic: "
                 << result.second;
        LOG_INFO << data.second.toStyledString();

    } else {
        LOG_INFO << "Match Error!!!";
    }
}
