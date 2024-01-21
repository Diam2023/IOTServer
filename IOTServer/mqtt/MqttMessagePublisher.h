//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_MQTTMESSAGEPUBLISHER_H
#define IOTSERVER_MQTTMESSAGEPUBLISHER_H

#include "Common.h"

#include <tuple>
#include <string>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "MqttClient.h"
#include <QThread>
#include <QObject>
#include <QCoreApplication>

namespace mqtt {

    class MqttMessagePublisher : public QObject {
    Q_OBJECT

    private:

        QCoreApplication *app;

        // Message Queue
        std::queue<MqttMessagePublisherPackage> messageQueue;
        std::mutex messageQueueMutex;
        std::condition_variable messageQueueCondVar;

    public:
        explicit MqttMessagePublisher(QObject *parent = 0);

//    Q_SIGNALS:
//
//        void publishSignal(const MqttMessagePublisherPackage &pkg);

    public Q_SLOTS:

        void workerOnce();

    public:
        void sendMessage(const MqttMessagePublisherPackage &pkg);

    SINGLETON_INTERFACE(MqttMessagePublisher);
    };
};


#endif //IOTSERVER_MQTTMESSAGEPUBLISHER_H
