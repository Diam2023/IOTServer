//
// Created by diam on 24-1-15.
//

#ifndef IOTSERVER_TOPICAPI_H
#define IOTSERVER_TOPICAPI_H

#include <future>


namespace api {

    class TopicApi {

    public:
        /**
         * insert Topic
         * @param name
         * @param data
         * @param qos
         * @param level
         * @return
         */
        static std::future<bool> addTopic(const std::string& name, const std::string& data, uint8_t qos, uint32_t level);
    };

} // api

#endif //IOTSERVER_TOPICAPI_H
