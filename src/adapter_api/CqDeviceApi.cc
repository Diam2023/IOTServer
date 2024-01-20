//
// Created by diam on 24-1-20.
//

#include "CqDeviceApi.h"

#include "DeviceApi.h"
#include "UserApi.h"
#include <drogon/drogon.h>

#include "SubscribeMap.h"
#include "Topic.h"

using namespace drogon;
using namespace drogon::orm;
//using namespace drogon::nosql;
using namespace drogon_model::iot_server;

namespace cq {

    std::future<bool> CqDeviceApi::addDevice(const std::string &sn, const std::string &name) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->queueInLoop([prom, sn, name]() {
            Device device;
            device.setDeviceSn(sn);
            device.setDeviceName(name);
            try {
                prom->set_value(api::DeviceApi::newDevice(device).get());
            } catch (const std::exception &e) {
                prom->set_exception(std::current_exception());
            }
        });

        return prom->get_future();
    }

    std::future<bool> CqDeviceApi::removeDevice(const std::string &sn) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->queueInLoop([prom, sn]() {
            auto dbClientPtr = app().getDbClient();
            Mapper<Device> deviceMapper(dbClientPtr);
            Mapper<SubscribeMap> subscribeMapper(dbClientPtr);
            Mapper<Topic> topicMapper(dbClientPtr);

            // TODO Wait Test

            auto device = deviceMapper.findFutureOne(Criteria(Device::Cols::_device_sn, CompareOperator::EQ, sn)).get();
            const auto &deviceId = device.getDeviceId();
            subscribeMapper.deleteBy(Criteria(SubscribeMap::Cols::_target_device_id, CompareOperator::EQ, *deviceId));
            topicMapper.deleteBy(Criteria(Topic::Cols::_target_device_id, CompareOperator::EQ, *deviceId));

            deviceMapper.deleteBy(Criteria(Device::Cols::_device_sn, CompareOperator::EQ, sn), [prom](const auto &r) {
                prom->set_value(r > 0);
            }, [prom](const auto &e) {
                prom->set_exception(std::current_exception());
            });
        });

        return prom->get_future();
    }

    std::future<std::shared_ptr<std::vector<Device>>> CqDeviceApi::listDevices() {

        auto prom = std::make_shared<std::promise<std::shared_ptr<std::vector<Device>>>>();

        drogon::app().getLoop()->queueInLoop([prom]() {
            auto dbClientPtr = app().getDbClient();
            Mapper<Device> deviceMapper(dbClientPtr);
            deviceMapper.findAll([prom](const auto &r) {
                auto res = std::make_shared<std::vector<Device>>(r);
                prom->set_value(res);
            }, [prom](const auto &e) {
                prom->set_exception(std::current_exception());
            });
        });

        return prom->get_future();
    }
} // cq