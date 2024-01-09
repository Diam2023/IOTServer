//
// Created by Monoliths on 4/23/2023.
//

#include <thread>
#include <QtCore/QCoreApplication>
#include <drogon/HttpAppFramework.h>

// Handler Exit Signal
static void exitSignalHandler() {
    // Handle Exit Signal
    LOG_WARN << "Server Exiting...";
    drogon::app().quit();
    QCoreApplication::exit();
}

static int runServer() {
    // Drogon Thread
    auto drogonThread = std::thread([]() {
        // Handler Exit Signal
        drogon::app().setIntSignalHandler(&exitSignalHandler);
        drogon::app().setTermSignalHandler(&exitSignalHandler);

        // Load config file
        drogon::app().loadConfigFile("../config/config.yaml");
        LOG_INFO << "Document Root: " << drogon::app().getDocumentRoot();

        // Get Customer Config
        auto config = drogon::app().getCustomConfig();
//        auto res = config.get("mqtt", nullptr);
//        res.isNull();
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

    return runServer();
}
