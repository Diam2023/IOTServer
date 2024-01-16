//
// Created by diam on 24-1-16.
//

#ifndef IOTSERVER_TOPICAPI_H
#define IOTSERVER_TOPICAPI_H

#include <future>
#include <string>


#include "Device.h"
#include "Topic.h"

namespace api {

    class TopicApi {

    public:

        /**
         * New Topic to topic table
         * @param topic
         * @return true if successful
         */
        static std::future<bool> newTopic(const drogon_model::iot_server::Topic &topic);

        /**
         * Delete Topic for topic table
         * @param topicId
         * @return
         */
        static std::future<bool> deleteTopic(uint32_t topicId) noexcept(false);


        /**
         * Get topic target device instance
         * @param topicId
         * @return
         */
        static std::future<drogon_model::iot_server::Device> getTargetDevice(uint32_t topicId);
    };

} // api

#endif //IOTSERVER_TOPICAPI_H
