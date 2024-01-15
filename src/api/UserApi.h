//
// Created by diam on 24-1-13.
//

#ifndef IOTSERVER_USERAPI_H
#define IOTSERVER_USERAPI_H

#include <future>
#include <json/value.h>
#include <memory>

#include "Users.h"

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
        static std::future<bool> logout(const std::string_view &token) noexcept(false);

        /**
         * return user id if logged in
         * @param token token for redis
         * @return id if successful
         */
        static std::future<std::string> getUserId(const std::string& token);
    };

} // api

#endif //IOTSERVER_USERAPI_H
