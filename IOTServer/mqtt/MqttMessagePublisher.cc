//
// Created by diam on 24-1-20.
//

#include "MqttMessagePublisher.h"

#include "MqttClient.h"

#include <QObject>

namespace mqtt {

    MqttMessagePublisher::MqttMessagePublisher(QObject *parent) : QObject(parent) {
    }

    void MqttMessagePublisher::workerOnce() {
        using namespace std::chrono_literals;

        if (messageQueue.empty())
        {
            return;
        }
        MqttMessagePublisherPackage pkg;
        {
            std::unique_lock<std::mutex> ul(messageQueueMutex);
            messageQueueCondVar.wait(ul, [this]() {
                return !messageQueue.empty();
            });
            pkg = messageQueue.front();
            messageQueue.pop();
        } // Release Lock

        mqtt::MqttClient::instance().publish(pkg);

//        emit MqttClient::instance().publish(pkg);
    }

    void MqttMessagePublisher::sendMessage(const MqttMessagePublisherPackage &pkg) {
        std::lock_guard<std::mutex> lg(messageQueueMutex);
        messageQueue.push(pkg);
        messageQueueCondVar.notify_one();
    }
};