//
// Created by 35691 on 10/9/2023.
//

#include "MqttClient.h"
#include <QMqttMessage>

namespace mqtt {
    void MqttClient::loadConfig(const Json::Value &value) {
        auto hostRes = value.get("host", DEFAULT_HOST);
        auto portRes = value.get("port", DEFAULT_PORT);

        if (!hostRes.isString()) {
            throw std::invalid_argument("host invalid");
        }
        if (!portRes.isNumeric()) {
            throw std::invalid_argument("port invalid");
        }

        // TODO Add SSL

        client.setPort(portRes.asInt64());
        // Default Encode utf8
        client.setHostname(QString::fromStdString(hostRes.asString()));
//        QMqttSubscriptionPropertiesDatatde
        client.subscribe(QMqttTopicFilter("#"));

        connect(&client, SIGNAL(client.messageReceived()), this, SLOT(messageHandler()));
    }

    void MqttClient::messageHandler(const QByteArray &message, const QMqttTopicName &topic) {
        // 该类任务：
        // messageHandler将订阅所有消息，并将消息放入队列
        // 使用一个消费者类将该类接收到的数据按时间最后状态过滤发送到Mysql
        // 具体细节，消费者类
        // 生产者（该类）创建就更新Redis缓存的Topic然后 Task1从Redis获取应该监听的主题，并将监听主题的数据送入待发送队列，同时检查Redis数据过期时间，过期则更新
        // 当数据过多时增大缓冲区？
        // 消费者类Task实时获取消生产者的数据队列，有则更新Mysql数据

        // set Timeout 500ms
        // drogon::app().getRedisClient()->setTimeout(500);
        // if (topic)

        // update command
        Json::Value obj;
        Json::Reader reader;
        reader.parse(message.toStdString(), obj);
        for (auto &cb: callbackChan) {
            cb.notify({topic, obj});
        }
    }

    template<class T>
    void MqttClient::registerNotifyCallback(const Notify &cb) {
        callbackChan.push_back(cb);
    }

} // mqtt