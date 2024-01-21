//
// Created by diam on 24-1-15.
//

#ifndef IOTSERVER_DEVICEAPI_H
#define IOTSERVER_DEVICEAPI_H

#include <future>
#include <string>


#include "Device.h"
#include "Topic.h"

namespace api {

    class DeviceApi {

    public:
        /**
         * Register a new iot Device and topic to sys
         * @param device device instance
         * @return true if not exists before
         */
        static std::future<bool>
        newDevice(const drogon_model::iot_server::Device &device,
                  const std::vector<drogon_model::iot_server::Topic> &topics) noexcept(false);

        /**
         * New Device Default sub all message
         * @param device
         * @return
         */
        static std::future<bool>
        newDevice(const drogon_model::iot_server::Device &device) noexcept(false);

        /**
         * Delete Device And delete the topic associated with it
         * @param deleteTopics device id
         * @param topics true delete all topic for device
         * @return if delete
         */
        static std::future<bool> deleteDevice(uint32_t deviceId, bool deleteTopics = true) noexcept(false);

        /**
         * Get Device all topic info
         * @param deviceId deviceId
         * @return topics
         */
        static std::future<std::vector<drogon_model::iot_server::Topic>> getDeiceTopicInfo(uint32_t deviceId);
    };
} // api

#endif //IOTSERVER_DEVICEAPI_H
