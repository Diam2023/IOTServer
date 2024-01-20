//
// Created by diam on 24-1-20.
//

#include "CqCommand.h"

#include "CqUserApi.h"
#include "CqDeviceApi.h"
#include "CqSubscribeApi.h"
#include "CqAliasApi.h"
#include "CqActionApi.h"

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

                // Check If Non login
                try {
                    cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start logout
                    cq::CqUserApi::logout(senderId).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Logout Successful");
                } catch (const std::exception &e) {
                    std::string errMsg = "Login Failed: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool addDeviceMatch = std::regex_match(message, addDeviceRegex);
            if (addDeviceMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }
                // TODO Add Permission Check

                try {
                    // start add device
                    std::sregex_iterator device(message.cbegin(), message.cend(), addDeviceRegex);
                    cq::CqDeviceApi::addDevice(device->str(1), device->str(2)).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Add Successful");
                } catch (const std::exception &e) {
                    std::string errMsg = "Add Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool removeDeviceMatch = std::regex_match(message, removeDeviceRegex);
            if (removeDeviceMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start remove device
                    std::sregex_iterator device(message.cbegin(), message.cend(), removeDeviceRegex);
                    if (cq::CqDeviceApi::removeDevice(device->str(1)).get()
                            ) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Remove Successful");
                    } else {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Removed");
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "Remove Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool listDeviceMatch = std::regex_match(message, listDeviceRegex);
            if (listDeviceMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start get devices
                    auto res = cq::CqDeviceApi::listDevices().get();

                    if (res->empty()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Device list Empty");
                    } else {
                        std::stringstream ss;
                        for (const auto &device: *res) {
                            ss << "------DEVICE------" << std::endl;
                            ss << "SN: " << *device.getDeviceSn() << std::endl;
                            ss << "NAME: " << *device.getDeviceName();
                        }
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, ss.str());
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "List Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }


            bool listSubscribeDeviceMessageMatch = std::regex_match(message, listSubscribeDeviceMessageRegex);
            if (listSubscribeDeviceMessageMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start get all Subscribe
                    auto res = cq::CqSubscribeApi::listAllSubscribe(token).get();

                    if (res->empty()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Topic list Empty");
                    } else {
                        std::sort(res->begin(), res->end(), [](auto fir, auto sec) -> bool {
                            const Device &firDevice = fir.first;
                            const Device &secDevice = sec.first;
                            return *firDevice.getDeviceId() < *secDevice.getDeviceId();
                        });
                        std::stringstream ss;

                        uint32_t prevDeviceId = 0;

                        for (const auto &deviceTopic: *res) {
                            if (prevDeviceId != *deviceTopic.first.getDeviceId()) {
                                ss << "------DEVICE------" << std::endl;
                                ss << "SN: " << *deviceTopic.first.getDeviceSn() << std::endl;
                                ss << "NAME: " << *deviceTopic.first.getDeviceName() << std::endl;
                                ss << "------TOPIC-------" << std::endl;
                                ss << "NAME: " << *deviceTopic.second.getTopicName() << std::endl;
                                prevDeviceId = *deviceTopic.first.getDeviceId();
                            } else {
                                ss << "NAME: " << *deviceTopic.second.getTopicName() << std::endl;
                            }
                        }
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, ss.str());
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "List Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }


            bool subscribeDeviceMessageMatch = std::regex_match(message, subscribeDeviceMessageRegex);
            if (subscribeDeviceMessageMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }
                // TODO Add Permission Check

                try {
                    // start Subscribe
                    std::sregex_iterator subscribe(message.cbegin(), message.cend(), subscribeDeviceMessageRegex);
                    cq::CqSubscribeApi::subscribeDeviceTopic(token, subscribe->str(1), subscribe->str(2)).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Subscribe Successful");
                } catch (const std::exception &e) {
                    std::string errMsg = "Subscribe Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            // unsubscribeDeviceMessage
            bool unsubscribeDeviceMessageMatch = std::regex_match(message, unsubscribeDeviceMessageRegex);
            if (unsubscribeDeviceMessageMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start Unsubscribe
                    std::sregex_iterator unsubscribe(message.cbegin(), message.cend(), unsubscribeDeviceMessageRegex);
                    if (cq::CqSubscribeApi::unsubscribeDeviceTopic(token, unsubscribe->str(1),
                                                                   unsubscribe->str(2)).get()
                            ) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Unsubscribe Successful");
                    } else {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Unsubscribed");
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "Unsubscribe Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool addDeviceAliasMatch = std::regex_match(message, addDeviceAliasRegex);
            if (addDeviceAliasMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start remove device
                    std::sregex_iterator alias(message.cbegin(), message.cend(), addDeviceAliasRegex);
                    cq::CqAliasApi::addAlias(token, alias->str(1), alias->str(2)).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Add Alias Successful");
                } catch (const std::exception &e) {
                    std::string errMsg = "Add Alias Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool removeDeviceAliasMatch = std::regex_match(message, removeDeviceAliasRegex);
            if (removeDeviceAliasMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }
                // TODO Add Permission Check

                try {
                    // start add device
                    std::sregex_iterator device(message.cbegin(), message.cend(), removeDeviceAliasRegex);
                    if (cq::CqAliasApi::removeAlias(token, device->str(1)).get()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Remove Alias Successful");
                    } else {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Removed");
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "Remove Alias Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool listDeviceAliasMatch = std::regex_match(message, listDeviceAliasRegex);
            if (listDeviceAliasMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start get devices
                    auto res = cq::CqAliasApi::listAlias(token).get();

                    if (res->empty()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Alias list Empty");
                    } else {

                        // Sort it by device id
                        std::sort(res->begin(), res->end(), [](auto fir, auto sec) -> bool {
                            const Device &firDevice = fir.first;
                            const Device &secDevice = sec.first;
                            return *firDevice.getDeviceId() < *secDevice.getDeviceId();
                        });
                        std::stringstream ss;

                        uint32_t prevDeviceId = 0;

                        for (const auto &deviceAlias: *res) {
                            if (prevDeviceId != *deviceAlias.first.getDeviceId()) {
                                ss << "------DEVICE------" << std::endl;
                                ss << "SN: " << *deviceAlias.first.getDeviceSn() << std::endl;
                                ss << "NAME: " << *deviceAlias.first.getDeviceName() << std::endl;
                                ss << "------ALIAS-------" << std::endl;
                                ss << "NAME: " << *deviceAlias.second.getAliasName() << std::endl;
                                prevDeviceId = *deviceAlias.first.getDeviceId();
                            } else {
                                ss << "NAME: " << *deviceAlias.second.getAliasName() << std::endl;
                            }
                        }
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, ss.str());
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "Alias List Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }


            bool listActionMatch = std::regex_match(message, listActionRegex);
            if (listActionMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start get devices
                    auto res = cq::CqActionApi::listAction(token).get();

                    if (res->empty()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Action list Empty");
                    } else {

                        // Sort it by device id
                        std::sort(res->begin(), res->end(), [](auto fir, auto sec) -> bool {
                            const Device &firDevice = std::get<0>(fir);
                            const Device &secDevice = std::get<0>(fir);
                            if (*firDevice.getDeviceId() == *secDevice.getDeviceId()) {
                                const Topic &firTopic = std::get<1>(fir);
                                const Topic &secTopic = std::get<1>(fir);

                                return *firTopic.getTopicId() < *secTopic.getTopicId();
                            } else {
                                return *firDevice.getDeviceId() < *secDevice.getDeviceId();
                            }
                        });
                        std::stringstream ss;

                        uint32_t prevDeviceId = 0;
                        uint32_t prevTopicId = 0;

                        for (const auto &deviceTopicAction: *res) {
                            if (prevDeviceId != *std::get<0>(deviceTopicAction).getDeviceId()) {
                                ss << "------DEVICE------" << std::endl;
                                ss << "SN: " << *std::get<0>(deviceTopicAction).getDeviceSn() << std::endl;
                                ss << "NAME: " << *std::get<0>(deviceTopicAction).getDeviceName() << std::endl;

                                if (prevTopicId != *std::get<1>(deviceTopicAction).getTopicId()) {
                                    ss << "------TOPICS-------" << std::endl;
                                    ss << "NAME: " << *std::get<1>(deviceTopicAction).getTopicName() << std::endl;

                                    ss << "------ACTIONS-------" << std::endl;
                                    ss << "NAME: " << *std::get<2>(deviceTopicAction).getActionName() << std::endl;

                                    prevTopicId = *std::get<1>(deviceTopicAction).getTopicId();
                                } else {
                                    ss << "NAME: " << *std::get<2>(deviceTopicAction).getActionName() << std::endl;
                                }

                                prevDeviceId = *std::get<0>(deviceTopicAction).getDeviceId();
                            } else {
                                if (prevTopicId != *std::get<1>(deviceTopicAction).getTopicId()) {
                                    ss << "------TOPICS-------" << std::endl;
                                    ss << "NAME: " << *std::get<1>(deviceTopicAction).getTopicName() << std::endl;

                                    ss << "------ACTIONS-------" << std::endl;
                                    ss << "NAME: " << *std::get<2>(deviceTopicAction).getActionName() << std::endl;

                                    prevTopicId = *std::get<1>(deviceTopicAction).getTopicId();
                                } else {
                                    ss << "NAME: " << *std::get<2>(deviceTopicAction).getActionName() << std::endl;
                                }
                            }
                        }
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, ss.str());
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "Alias List Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool makeActionMatch = std::regex_match(message, makeActionRegex);
            if (makeActionMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }

                try {
                    // start remove Action
                    std::sregex_iterator action(message.cbegin(), message.cend(), makeActionRegex);
                    cq::CqActionApi::addAction(token, action->str(1), action->str(2), action->str(3),
                                               action->str(4)).get();
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Make Action Successful");
                } catch (const std::exception &e) {
                    std::string errMsg = "Make Action Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }

            bool deleteActionMatch = std::regex_match(message, deleteActionRegex);
            if (deleteActionMatch) {

                std::string token;
                // Check If Non Login
                try {
                    token = cq::CqUserApi::getLoginInfo(senderId).get();
                } catch (const std::exception &e) {
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Login First!");
                    break;
                }
                // TODO Add Permission Check

                try {
                    // start Delete Action
                    std::sregex_iterator action(message.cbegin(), message.cend(), deleteActionRegex);
                    if (cq::CqActionApi::removeAction(token, action->str(1)).get()) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Remove Action Successful");
                    } else {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId, "Removed");
                    }
                } catch (const std::exception &e) {
                    std::string errMsg = "Remove Action Error: ";
                    errMsg.append(e.what());
                    cq::CqMessageManager::getInstance().messageOut(botId, senderId, errMsg);
                }
                break;
            }


            std::string token;
            // Check If Non Login
            try {
                token = cq::CqUserApi::getLoginInfo(senderId).get();
            } catch (const std::exception &e) {
                // Non Login
            }
            if (!token.empty()) {
                try {
                    auto res = CqActionApi::matchAction(token, message).get();
                    if (res) {
                        cq::CqMessageManager::getInstance().messageOut(botId, senderId,
                                                                       "Matched Action");
                        break;
                    }
                } catch (const std::exception &e) {
                    // Non Match
                }
            }


            cq::CqMessageManager::getInstance().messageOut(botId, senderId,
                                                           "Non Matched Command Please use help display command list");

        } while (false);
    }

    CqCommand::CqCommand() : commandWorkThread(&CqCommand::handlerCommand, this) {
        loginRegex = std::regex("login (.*) (.*)");
        logoutRegex = std::regex("logout");

        addDeviceRegex = std::regex("add device (.*) (.*)");
        removeDeviceRegex = std::regex("remove device (.*)");
        listDeviceRegex = std::regex("list devices");

        subscribeDeviceMessageRegex = std::regex("subscribe (.*) (.*)");
        unsubscribeDeviceMessageRegex = std::regex("unsubscribe (.*) (.*)");
        listSubscribeDeviceMessageRegex = std::regex("list subscribes");

        listDeviceAliasRegex = std::regex("list alias");
        addDeviceAliasRegex = std::regex("add alias (.*) (.*)");
        removeDeviceAliasRegex = std::regex("remove alias (.*)");

        listActionRegex = std::regex("list actions");
        // 定义操作 {操作名} {设备名/别名} {subtopic} {JSON数据}
        makeActionRegex = std::regex("define (.*) (.*) (.*) (.*)");
        deleteActionRegex = std::regex("del-define (.*)");

        helpRegex = std::regex("help");
    }
} // cq