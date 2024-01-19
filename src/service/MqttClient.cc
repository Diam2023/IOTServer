//
// Created by 35691 on 10/9/2023.
//

#include "MqttClient.h"
#include "MqttMessageHandler.h"
#include <QMqttMessage>

namespace mqtt {
    MqttClient &MqttClient::loadConfig(const Json::Value &value) {
        auto hostRes = value.get("host", DEFAULT_HOST);
        auto portRes = value.get("port", DEFAULT_PORT);

        if (!hostRes.isString()) {
            throw std::invalid_argument("host invalid");
        }
        if (!portRes.isNumeric()) {
            throw std::invalid_argument("port invalid");
        }

        LOG_INFO << "load mqtt host: " << hostRes.asString() << " port: " << portRes.asInt64();

        clientPtr->setPort(portRes.asInt64());
        // Default Encode utf8
        clientPtr->setHostname(QString::fromStdString(hostRes.asString()));

        return *this;
    }

    void MqttClient::connected() {
        LOG_INFO << "Mqtt Connected";
        clientPtr->subscribe(QMqttTopicFilter("#"));
        isConnected = true;
    }

    void MqttClient::disconnected() {
        LOG_INFO << "Mqtt Disconnected";
        isConnected = false;
        if (clientPtr->error() != QMqttClient::NoError) {
            abort();
            LOG_ERROR << qt_getEnumName(clientPtr->error()) << " Enum Value: " << (int) clientPtr->error();
        }
    }

    void MqttClient::start() {
        // TODO Add SSL
        clientPtr->setAutoKeepAlive(true);

        clientPtr->connectToHost();

        LOG_INFO << "Mqtt Start";
    }

    MqttClient::MqttClient() : isConnected(false), clientPtr(new QMqttClient(this)) {

        QObject::connect(clientPtr.data(), &QMqttClient::connected, this, &MqttClient::connected);
        QObject::connect(clientPtr.data(), &QMqttClient::disconnected, this, &MqttClient::disconnected);

        // First
        QObject::connect(clientPtr.data(), &QMqttClient::messageReceived, &mqtt::MqttMessageHandler::getInstance(),
                         &mqtt::MqttMessageHandler::messageHandler);

        // Second
        QObject::connect(clientPtr.data(), &QMqttClient::messageReceived,
                         [this](const QByteArray &message, const QMqttTopicName &topic) -> void {
                             // messageHandler将订阅所有消息，并将消息放入队列
                             // 使用一个消费者类将该类接收到的数据按时间最后状态过滤发送到Mysql
                             // 具体细节，消费者类
                             // 生产者（该类）创建就更新Redis缓存的Topic然后 Task1从Redis获取应该监听的主题，并将监听主题的数据送入待发送队列，同时检查Redis数据过期时间，过期则更新
                             // 当数据过多时增大缓冲区？
                             // 消费者类Task实时获取消生产者的数据队列，有则更新Mysql数据

                             Json::Value obj;
                             Json::Reader reader;
                             reader.parse(message.toStdString(), obj);
                             for (auto &cb: this->callbackChain) {
                                 cb.notify({topic, obj});
                             }
                         });
    }

    void MqttClient::stop() {
        if (isConnected || clientPtr->state() == QMqttClient::Connected) {
            clientPtr->disconnectFromHost();
        }
    }

    template<class T>
    void MqttClient::registerNotifyCallback(const MessageNotify &cb) {
        callbackChain.push_back(cb);
    }

} // mqtt