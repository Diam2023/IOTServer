//
// Created by 35691 on 10/9/2023.
//

#ifndef IOTSERVER_MQTTCLIENT_H
#define IOTSERVER_MQTTCLIENT_H

#include <QMqttClient>
#include <json/value.h>
#include <drogon/drogon.h>
#include <vector>

namespace mqtt {
    static const char *DEFAULT_HOST = "mqtt://127.0.0.1";
    static const int DEFAULT_PORT = 1883;

    // MqttData Disrupt
    using MqttData = std::pair<QMqttTopicName, Json::Value>;

    class MessageNotify {
    public:
        virtual void notify(MqttData &&) = 0;
    };

    // Mqtt Client
    class MqttClient final : public QObject {
    private:
        QMqttClient client;

        std::vector<MessageNotify> callbackChain;

    public:
        MqttClient() = default;

        ~MqttClient() override = default;

        void loadConfig(const Json::Value &value) noexcept(false);

        /**
         * Register A Notify Class For mqtt message
         * @tparam T
         */
        template<class T>
        void registerNotifyCallback(const MessageNotify &);

        inline static MqttClient &instance() {
            static MqttClient client;
            return client;
        };
    };

} // mqtt

#endif //IOTSERVER_MQTTCLIENT_H
