//
// Created by Monoliths on 4/23/2023.
//

#include <thread>
#include <QtCore/QCoreApplication>
#include <drogon/HttpAppFramework.h>
#include "MqttClient.h"
#include <QTimer>

#include "CqMqttDeviceMessageHandler.h"
#include "CqMessageManager.h"

#include "MqttMessagePublisher.h"
#include <QSharedPointer>

static QSharedPointer<QTimer> publisherWorkerPtr;

// Handler Exit Signal
static void exitSignalHandler() {
    // Handle Exit Signal
    LOG_WARN << "Server Exiting...";
    mqtt::MqttClient::instance().stop();
    drogon::app().quit();
    QCoreApplication::exit();
}

static int runServer() {
    using namespace std::chrono_literals;

    // Drogon Thread
    auto drogonThread = std::thread([]() {
        // Handler Exit Signal
        drogon::app().setIntSignalHandler(&exitSignalHandler);
        drogon::app().setTermSignalHandler(&exitSignalHandler);

        // Load config file
        drogon::app().loadConfigFile("../config/config.yaml");
        LOG_INFO << "Document Root: " << drogon::app().getDocumentRoot();

        // Get Customer Config
        // auto config = drogon::app().getCustomConfig();
        // Run HTTP framework,the method will block in the internal event loop
        drogon::app().run();
    });

    auto result = QCoreApplication::exec();

    // If Drogon Thread Not Exit Yet.
    if (drogonThread.joinable()) {
        // Wait To Exit
        drogonThread.join();
    }

    LOG_INFO << "Server Exit With Code: " << result;

    return result;
}

// Main Process
int main(int argc, char **argv) {
    // Qt Core Application
    QCoreApplication app(argc, argv);

    QTimer::singleShot(500, &app, [&app]() {
        // 因为QMqttClient依赖于socket所以在不同线程中启动与发布会出现 qsocketnotifier: socket notifiers cannot be enabled or disabled from another thread 问题
        // 但是QMqttClient在其他线程启动后不工作，status卡在Connecting也不抛出错误 所以很头疼
        // https://forum.qt.io/topic/109138/qmqttclient-connection-not-made-from-another-thread 方案不适用
        // 最后解决方案Client在QtEventLoop中启动 Publish也在事件循环中调用
        mqtt::MqttClient::instance().registerNotifyCallback(cq::CqMqttDeviceMessageHandler::getInstance());

        // Load Mqtt Launch Mqtt start!
        mqtt::MqttClient::instance().loadConfig(drogon::app().getCustomConfig()["mqtt"]).start();

        publisherWorkerPtr.reset(new QTimer(&app));

        QObject::connect(publisherWorkerPtr.data(), &QTimer::timeout, &mqtt::MqttMessagePublisher::getInstance(),
                         &mqtt::MqttMessagePublisher::workerOnce);
        publisherWorkerPtr->start(50);
    });

    return runServer();
}
