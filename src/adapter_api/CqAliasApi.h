//
// Created by diam on 24-1-20.
//
#pragma once

#include <string>

#include <future>
#include <vector>

#include "UserDeviceAliasMap.h"

using namespace drogon_model::iot_server;

namespace cq {

    class CqAliasApi {

    public:


        /**
         * Add Alias To Database
         * @param token
         * @param sn
         * @param alias
         * @return
         */
        static std::future<bool> addAlias(const std::string &token, const std::string &sn, const std::string &alias);

        /**
         * Remove Alias
         * @param token
         * @param alias
         * @return
         */
        static std::future<bool> removeAlias(const std::string &token, const std::string &alias);

        /**
         * List alias
         * @param token
         * @return
         */
        static std::future<std::shared_ptr<std::vector<std::pair<Device, UserDeviceAliasMap>>>>
        listAlias(const std::string &token);
    };

} // cq


