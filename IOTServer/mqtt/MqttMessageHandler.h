//
// Created by diam on 24-1-9.
//

#ifndef IOTSERVER_MQTTMESSAGEHANDLER_H
#define IOTSERVER_MQTTMESSAGEHANDLER_H

#include <QObject>

#include <QMqttClient>
#include <QMqttTopicName>
#include <json/value.h>
#include "MqttClient.h"

namespace mqtt {

    // Default Handler
    class MqttMessageHandler {

    public:
        MqttMessageHandler() = default;

        virtual ~MqttMessageHandler() = default;

        virtual void handler(const MqttData &data) = 0;

        void operator()(const MqttData &data) { handler(data); };
    };

} // mqtt

#endif //IOTSERVER_MQTTMESSAGEHANDLER_H
