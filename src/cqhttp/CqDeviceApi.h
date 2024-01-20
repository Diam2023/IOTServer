//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQDEVICEAPI_H
#define IOTSERVER_CQDEVICEAPI_H

#include <string>

#include <future>
#include <vector>

#include "Device.h"

using namespace drogon_model::iot_server;

namespace cq {

    class CqDeviceApi {
    public:

        static std::future<bool> addDevice(const std::string &sn, const std::string &name);

        static std::future<bool> removeDevice(const std::string &sn);

        static std::future<std::shared_ptr<std::vector<Device>>> listDevices();
    };

} // cq

#endif //IOTSERVER_CQDEVICEAPI_H
