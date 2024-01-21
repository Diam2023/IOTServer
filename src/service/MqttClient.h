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
    static const char *DEFAULT_HOST = "localhost";
    static const int DEFAULT_PORT = 1883;


    using MqttData = std::pair<QMqttTopicName, Json::Value>;
    // MqttData Disrupt
    using MqttHandlerType = std::function<void(const MqttData &)>;

    /**
     * DeviceSN Topic Qos Json
     */
    using MqttMessagePublisherPackage = std::tuple<std::string, std::string, uint8_t, std::string>;

    // Mqtt Client
    class MqttClient final : public QObject {
    private:
        QMqttClient* clientPtr;

        std::vector<MqttHandlerType> callbacks;

        std::atomic<bool> isConnected;

    public:

        void moveToThread(QThread *thread);

        bool checkIsConnected() { return isConnected; };

        MqttClient();

        ~MqttClient() override = default;

        MqttClient &loadConfig(const Json::Value &value) noexcept(false);


        void stop();

        /**
         * Register A Notify Class For mqtt message
         */
        void registerNotifyCallback(const MqttHandlerType &);

        inline static MqttClient &instance() {
            static MqttClient client;
            return client;
        };

        void start();

        void publish(const MqttMessagePublisherPackage& pkg);

    public slots:

        void connected();

        void disconnected();

        void messageReceived(const QByteArray &message, const QMqttTopicName &topic);
    };


} // mqtt

#endif //IOTSERVER_MQTTCLIENT_H
