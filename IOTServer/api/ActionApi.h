//
// Created by diam on 24-1-20.
//

#pragma once

#include <string>

#include <future>
#include <vector>

#include "UserDeviceActionMap.h"
#include "Topic.h"
#include "Device.h"
#include "MqttClient.h"

namespace api {

    class ActionApi {

    public:

        /**
         * define a action
         * @param token
         * @param name
         * @param sn
         * @param topic create if not exists
         * @param json
         * @return
         */
        static std::future<bool>
        addAction(const std::string &token, const std::string &name, const std::string &sn, const std::string &topic,
                  const std::string &json);

        /**
         * Remove Alias
         * @param token
         * @param action
         * @return
         */
        static std::future<bool> removeAction(const std::string &token, const std::string &action);

        /**
         * List Action
         * @param token
         * @return
         */
        static std::future<std::shared_ptr<std::vector<std::tuple<drogon_model::iot_server::Device, drogon_model::iot_server::Topic, drogon_model::iot_server::UserDeviceActionMap>>>>
        listAction(const std::string &token);

        /**
         * Match Action
         * @param token
         * @param action
         * @return
         */
        static std::future<mqtt::MqttMessagePublisherPackage>
        matchAction(const std::string &token, const std::string &action);

        /**
         * Direct Send Message
         * @param token
         * @param sn
         * @param topic
         * @param json
         * @return
         */
        static void
        launchAction(const std::string &sn, const std::string &topic,
                     const std::string &json);
    };

};