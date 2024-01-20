//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQACTIONAPI_H
#define IOTSERVER_CQACTIONAPI_H

#include <string>

#include <future>
#include <vector>

#include "UserDeviceActionMap.h"
#include "Topic.h"
#include "Device.h"

using namespace drogon_model::iot_server;

namespace cq {

    class CqActionApi {

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
        static std::future<std::shared_ptr<std::vector<std::tuple<Device, Topic, UserDeviceActionMap>>>>
        listAction(const std::string &token);

        /**
         * Match Action
         * @param token
         * @param action
         * @return
         */
        static std::future<bool> matchAction(const std::string &token, const std::string &action);

        static std::future<bool> callAction(const std::string &token, const std::string &action);

        static std::future<bool> matchAndCallAction(const std::string &token, const std::string &action);
    };

} // cq

#endif //IOTSERVER_CQACTIONAPI_H
