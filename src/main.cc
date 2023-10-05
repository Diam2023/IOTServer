//
// Created by Monoliths on 4/23/2023.
//

#include <QtCore/QCoreApplication>
#include <thread>
#include <drogon/HttpAppFramework.h>

/**
 * Signal For Exit
 */
enum class ExitSignal{
    INT,
    TERM
};

// Handler Exit Signal
static inline void exitSignalHandler(ExitSignal)
{
    // 处理退出程序
    std::cout << "Exiting..." << std::endl;
    drogon::app().quit();
    QCoreApplication::exit();
}

static int startDrogonTask()
{
    // Drogon Thread
    auto drogonThread = std::thread([](){
        // Handler Exit Signal
        drogon::app().setIntSignalHandler([] { return exitSignalHandler(ExitSignal::INT); });
        drogon::app().setTermSignalHandler([](){ return exitSignalHandler(ExitSignal::TERM); });

        //Load config file
        drogon::app().loadConfigFile("/home/monoliths/Project/CMake/IOTServer/config/config.yaml");
        LOG_INFO << "Document Root: " <<  drogon::app().getDocumentRoot();

        // To get Customer Config
//        drogon::app().getCustomConfig().get()

        //Run HTTP framework,the method will block in the internal event loop
        drogon::app().run();
    });

    auto result = QCoreApplication::exec();

    // If Drogon Thread Not Exit Yet.
    if (drogonThread.joinable())
    {
        // Wait To Exit
        drogonThread.join();
    }

    return result;
}

// Main Process
int main(int argc, char **argv)
{
    // Qt Core Application
    QCoreApplication app(argc, argv);


    return startDrogonTask();
}

