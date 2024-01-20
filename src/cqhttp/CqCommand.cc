//
// Created by diam on 24-1-20.
//

#include "CqCommand.h"

#include "CqUserApi.h"

#include <future>
#include "CqMessageManager.h"

namespace cq {

    void CqCommand::pushCommand(const CqCommandData &command) {
        std::lock_guard<std::mutex> lg(commandQueueMutex);
        commandQueue.push(command);
        commandQueueCondVar.notify_one();
    }

    [[noreturn]] void CqCommand::handlerCommand() {
        using namespace std::chrono_literals;

        while (true) {
            CqCommandData data;
            {
                std::unique_lock<std::mutex> ul(commandQueueMutex);
                commandQueueCondVar.wait(ul, [this]() {
                    return !commandQueue.empty();
                });
                data = commandQueue.front();
                commandQueue.pop();
            } // Release Lock
            matchCommand(data);

            std::this_thread::sleep_for(50ms);
        }
    }

    void CqCommand::matchCommand(const CqCommandData &data) {

        auto botId = std::get<0>(data);
        auto senderId = std::get<1>(data);
        auto message = std::get<2>(data);

        // Check Logged in

        try {
            do {

                bool loginMatch = std::regex_match(message, loginRegex);
                if (loginMatch) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Test response");

//                    if (cq::CqUserApi::getLoginInfo(senderId).get().empty()) {
//                        std::sregex_iterator login(message.cbegin(), message.cend(), loginRegex);
//                        auto token = cq::CqUserApi::login(botId, senderId, login->str(1), login->str(2)).get();
//                    }

                    break;
                }
            } while (false);

        } catch (const std::exception &e) {

        }
    }

    CqCommand::CqCommand() : commandWorkThread(&CqCommand::handlerCommand, this) {
        loginRegex = std::regex("login (.*) (.*)");
        logoutRegex = std::regex("logout");

        addDeviceRegex = std::regex("add device (.*)");
        removeDeviceRegex = std::regex("remove device (.*)");
        listDeviceRegex = std::regex("list all device");

        subscribeDeviceMessageRegex = std::regex("subscribe message (.*)");
        unsubscribeDeviceMessageRegex = std::regex("unsubscribe message (.*)");
        listSubscribeDeviceMessageRegex = std::regex("list unsubscribe message");

        listDeviceAliasRegex = std::regex("list devices alias");
        addDeviceAliasRegex = std::regex("add device alias (.*)");
        removeDeviceAliasRegex = std::regex("remove device alias (.*)");

        // 定义操作 {操作名} {设备名/别名} {subtopic} {JSON数据}
        makeActionRegex = std::regex("define (.*) (.*) (.*) (.*)");
        deleteActionRegex = std::regex("logout");

        helpRegex = std::regex("help");
    }
} // cq