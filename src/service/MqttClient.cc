//
// Created by 35691 on 10/9/2023.
//

#include "MqttClient.h"
#include "MqttMessageFilter.h"
#include <QMqttMessage>

#include "Tools.h"
#include "json/json.h"

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

        // TODO TEST Data
        registerNotifyCallback([](const MqttData &data) {
            auto result = getDeviceSerialNumberAndSubTopic(data.first.name().toStdString());
            if (!result.first.empty()) {

                LOG_INFO << "Received SN: " << result.first << " Sub Topic: "
                         << result.second;
                LOG_INFO << data.second.toStyledString();

            } else {
                LOG_INFO << "Match Error!!!";
            }
        });

        // Message Received
        QObject::connect(clientPtr.data(), &QMqttClient::messageReceived, this, &MqttClient::messageReceived);
    }

    void MqttClient::stop() {
        if (isConnected || clientPtr->state() == QMqttClient::Connected) {
            clientPtr->disconnectFromHost();
        }
    }

    void MqttClient::registerNotifyCallback(const MqttHandlerType &cb) {
        callbacks.push_back(cb);
    }

    void MqttClient::messageReceived(const QByteArray &message, const QMqttTopicName &topic) {
        // Filter No Device
        if (!isDeviceTopic(topic.name().toStdString())) {
            LOG_INFO << "Filter Non Device";
            return;
        }

        // Filter NON Json Data
        Json::Value tree;
        Json::String err;
        Json::CharReaderBuilder reader;
        std::unique_ptr<Json::CharReader> const json_read(reader.newCharReader());
        auto msgString = message.toStdString();
        json_read->parse(msgString.c_str(), msgString.c_str() + msgString.length(), &tree, &err);

        if (!err.empty()) {
            LOG_INFO << "Ignore Non Json: " << topic.name().toStdString() << " msg: "
                     << message.toStdString();
            return;
        }

        auto data = std::make_pair(topic, tree);
        if (!DataBaseMqttTopicFilter::getInstance().doFilter(data)) {
            LOG_INFO << "NON Registered Device " << getDeviceSerialNumber(data.first.name().toStdString());
            return;
        }

        // Run Handlers
        for (auto &cb: this->callbacks) {
            cb(data);
        }
    }

} // mqtt