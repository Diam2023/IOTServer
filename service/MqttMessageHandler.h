//
// Created by diam on 24-1-9.
//

#ifndef IOTSERVER_MQTTMESSAGEHANDLER_H
#define IOTSERVER_MQTTMESSAGEHANDLER_H

#include <QObject>

#include <QMqttClient>
#include <QMqttTopicName>

namespace mqtt {


    // Default Handler
    class MqttMessageHandler : public QObject {
        QObject;

    public:

        static MqttMessageHandler &getInstance() {
            static MqttMessageHandler handler;
            return handler;
        }

        MqttMessageHandler() = default;

        virtual ~MqttMessageHandler() {};

    public slots:

        void messageHandler(const QByteArray &message, const QMqttTopicName &topic = QMqttTopicName());
    };

} // mqtt

#endif //IOTSERVER_MQTTMESSAGEHANDLER_H
