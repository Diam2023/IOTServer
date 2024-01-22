//
// Created by diam on 24-1-20.
//
#pragma once


#include <string>

#include <future>
#include <vector>

#include "SubscribeMap.h"
#include "Topic.h"
#include "Device.h"

namespace api {

    class SubscribeApi {

    public:

        /**
         * List all user subscribed topic
         * @param token
         * @return
         */
        static std::future<std::shared_ptr<std::vector<std::pair<drogon_model::iot_server::Device, drogon_model::iot_server::Topic>>>>
        listAllSubscribe(const std::string &token);


        /**
         * Subscribe a device
         *
         * This Api Will Create a Topic if Not exists
         *
         * @param token
         * @param sn
         * @param topic
         * @return
         */
        static std::future<bool>
        subscribeDeviceTopic(const std::string &token, const std::string &sn, const std::string &topic);

        /**
         * Subscribe device
         *
         * This Api Will Delete Topic if reference count equal 1
         *
         * @param token
         * @param sn
         * @param topic
         * @return
         */
        static std::future<bool>
        unsubscribeDeviceTopic(const std::string &token, const std::string &sn, const std::string &topic);
    };
};
