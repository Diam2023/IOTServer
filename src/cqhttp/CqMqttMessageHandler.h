//
// Created by diam on 24-1-19.
//

#pragma once

#include "MqttMessageHandler.h"

namespace cq {
    class CqMqttMessageHandler : public mqtt::MqttMessageHandler {

    public:
        CqMqttMessageHandler();

        /**
         * Message Handler
         * @param data
         */
        void handler(const mqtt::MqttData &data) override;

        static CqMqttMessageHandler &getInstance() {
            static CqMqttMessageHandler cqMqttMessageHandler;
            return cqMqttMessageHandler;
        }
    };
};
