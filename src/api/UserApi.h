//
// Created by diam on 24-1-13.
//

#ifndef IOTSERVER_USERAPI_H
#define IOTSERVER_USERAPI_H

#include <future>
#include <json/value.h>
#include <memory>

#include "User.h"

namespace api {

    /**
     * Api For adapter
     */
    class UserApi {

    public:

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
         * Add Device To User Device List
         * @param token user token
         * @param deviceId deviceId for add
         * @return if successful
         */
        static std::future<bool> addDevice(const std::string &token, const std::string &deviceId);
    };

} // api

#endif //IOTSERVER_USERAPI_H
