//
// Created by diam on 24-1-20.
//

#include "CqCommand.h"

#include "CqUserApi.h"

#include <future>
#include "CqMessageManager.h"
#include <drogon/drogon.h>
#include <sstream>

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


        do {
            // Help
            if (std::regex_match(message, helpRegex)) {
                std::stringstream ss;
                // show help message
                const auto helpMessageArray = drogon::app().getCustomConfig()["cqhttp"]["help"];
                for (const Json::Value &msg: helpMessageArray) {
                    ss << msg.asString() << std::endl;
                }
                cq::CqMessageManager::getInstance().messageOut(botId, senderId, ss.str());
                break;
            }

            // Login
            bool loginMatch = std::regex_match(message, loginRegex);
            if (loginMatch) {

                // Check If logged in
                try {
                    if (!cq::CqUserApi::getLoginInfo(senderId).get().empty()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Already Logged In");
                        break;
                    }
                } catch (const std::exception &e) {
                }

                try {
                    // Get Login argument usr and pwd
                    std::sregex_iterator login(message.cbegin(), message.cend(), loginRegex);
                    // start login
                    auto token = cq::CqUserApi::login(botId, senderId, login->str(1), login->str(2)).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, token);
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login Successful");
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login Failed");
                }
                break;
            }

            bool logoutMatch = std::regex_match(message, logoutRegex);
            if (logoutMatch) {

                std::string token;
                // Check If logged in
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                    if (token.empty()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                        break;
                    }
                } catch (const std::exception &e) {
                }

                try {
                    // start logout
                    cq::CqUserApi::logout(senderId).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Logout Successful");
                } catch (const std::exception &e) {
                    std::string errMsg = "Login Failed";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            cq::CqMessageManager::getInstance().messageOut(botId, senderId,
                                                           "Non Matched Command Please use help display command list");

        } while (false);
    }

    CqCommand::CqCommand() : commandWorkThread(&CqCommand::handlerCommand, this) {
        loginRegex = std::regex("login (.*) (.*)");
        logoutRegex = std::regex("logout");

        addDeviceRegex = std::regex("add device (.*)");
        removeDeviceRegex = std::regex("remove device (.*)");
        listDeviceRegex = std::regex("list all device");

        subscribeDeviceMessageRegex = std::regex("subscribe (.*) (.*)");
        unsubscribeDeviceMessageRegex = std::regex("unsubscribe (.*) (.*)");
        listSubscribeDeviceMessageRegex = std::regex("list subscribes");

        listDeviceAliasRegex = std::regex("list alias");
        addDeviceAliasRegex = std::regex("add alias (.*)");
        removeDeviceAliasRegex = std::regex("remove alias (.*)");

        // 定义操作 {操作名} {设备名/别名} {subtopic} {JSON数据}
        makeActionRegex = std::regex("define (.*) (.*) (.*) (.*)");
        deleteActionRegex = std::regex("del-define (.*)");

        helpRegex = std::regex("help");
    }
} // cq