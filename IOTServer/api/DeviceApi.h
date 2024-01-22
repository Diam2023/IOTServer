//
// Created by diam on 24-1-20.
//

#pragma once

#include <string>

#include <future>
#include <vector>

#include "Device.h"

namespace api {

    class DeviceApi {
    public:

        static std::future<bool> addDevice(const drogon_model::iot_server::Device &device);

        static std::future<bool> removeDevice(const std::string &sn);

        static std::future<std::shared_ptr<std::vector<drogon_model::iot_server::Device>>> listDevices();

        static std::future<drogon_model::iot_server::Device> getDevice(const std::string &sn);
    };
};

