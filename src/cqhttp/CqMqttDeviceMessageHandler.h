//
// Created by diam on 24-1-19.
//

#pragma once

#include "MqttMessageHandler.h"

namespace cq {
    class CqMqttDeviceMessageHandler : public mqtt::MqttMessageHandler {

    public:
        CqMqttDeviceMessageHandler();

        /**
         * Message Handler
         * @param data
         */
        void handler(const mqtt::MqttData &data) override;

        static CqMqttDeviceMessageHandler &getInstance() {
            static CqMqttDeviceMessageHandler cqMqttMessageHandler;
            return cqMqttMessageHandler;
        }
    };
}
