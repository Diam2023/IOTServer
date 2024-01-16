//
// Created by diam on 24-1-13.
//

#ifndef IOTSERVER_USERAPI_H
#define IOTSERVER_USERAPI_H

#include <future>
#include <json/value.h>
#include <memory>

#include "User.h"
#include "Device.h"
#include "Topic.h"

namespace api {

    /**
     * Api For adapter
     */
    class UserApi {

    public:
        // TODO Remove token

        /**
         * Login
         * @param key id or name
         * @param pwd password for user
         * @return result for token or null
         */
        static std::future<std::string>
        login(const std::string &key, const std::string &pwd) noexcept(false);

        /**
         * Logout
         * @param token token for redis
         * @return if successful
         */
        static std::future<bool> logout(const std::string &token) noexcept(false);

        /**
         * return user id if logged in
         * @param token token for redis
         * @return id if successful
         */
        static std::future<std::string> getUserId(const std::string &token);

        /**
         * get Permission level
         * @param token
         * @return level
         */
        static std::future<uint32_t> getUserPermissionLevel(const std::string &token);

        /**
         * Add Device To User Subscribe
         * @param token user token
         * @param deviceId deviceId for add
         * @return if successful
         */
        static std::future<bool> addDevice(const std::string &token, const std::string &deviceId);

        /**
         * Remove Device From User Subscribe
         * @param token
         * @param deviceId
         * @return
         */
        static std::future<bool> removeDevice(const std::string &token, const std::string &deviceId);


        /**
         * Add Topic To User Subscribe
         * @param token user token
         * @param deviceId
         * @param topicId topic for add
         * @return if successful
         */
        static std::future<bool> addTopic(const std::string &token, const std::string &deviceId, const std::string &topicId);

        /**
         * Remove Topic From User Subscribe
         * @param token
         * @param deviceId
         * @param topicId
         * @return
         */
        static std::future<bool> removeTopic(const std::string &token, const std::string &deviceId, const std::string &topicId);

        /**
         * Get All Device subscribed by user
         * @param userId
         * @return
         */
        static std::future<std::vector<drogon_model::iot_server::Device>>
        getAllSubscribedDevice(const std::string &userId);

        /**
         * Get All Device Topic subscribed by user
         * @param userId
         * @return
         */
        static std::future<std::vector<drogon_model::iot_server::Topic>>
        getSubscribedDeviceAllTopics(const std::string &userId, const std::string &deviceId);
    };

} // api

#endif //IOTSERVER_USERAPI_H
