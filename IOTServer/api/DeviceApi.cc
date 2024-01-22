//
// Created by diam on 24-1-20.
//

#include "DeviceApi.h"

#include "DeviceApi.h"
#include "UserApi.h"
#include <drogon/drogon.h>

#include "SubscribeMap.h"
#include "Topic.h"

using namespace drogon;
using namespace drogon::orm;
//using namespace drogon::nosql;
using namespace drogon_model::iot_server;

namespace api {

    std::future<bool> DeviceApi::addDevice(const drogon_model::iot_server::Device &device) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, device]() {
            auto dbClientPtr = app().getDbClient();
            Mapper<Device> deviceMapper(dbClientPtr);
            deviceMapper.insert(device, [prom](const auto &d) {
                prom->set_value(true);
            }, [prom](const auto &e) {
                prom->set_exception(std::current_exception());

            });
        });

        return prom->get_future();
    }

    std::future<bool> DeviceApi::removeDevice(const std::string &sn) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, sn]() {
            auto dbClientPtr = app().getDbClient();
            Mapper<Device> deviceMapper(dbClientPtr);
            Mapper<SubscribeMap> subscribeMapper(dbClientPtr);
            Mapper<Topic> topicMapper(dbClientPtr);

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

    std::future<std::shared_ptr<std::vector<Device>>> DeviceApi::listDevices() {

        auto prom = std::make_shared<std::promise<std::shared_ptr<std::vector<Device>>>>();

        drogon::app().getLoop()->runInLoop([prom]() {
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

    std::future<Device> DeviceApi::getDevice(const std::string &sn) {

        auto prom = std::make_shared<std::promise<Device>>();

        drogon::app().getLoop()->runInLoop([prom, sn]() {
            auto dbClientPtr = app().getDbClient();
            Mapper<Device> deviceMapper(dbClientPtr);
            deviceMapper.findOne(Criteria(Device::Cols::_device_sn, CompareOperator::EQ, sn), [prom](const auto &r) { ;
                prom->set_value(r);
            }, [prom](const auto &e) {
                prom->set_exception(std::current_exception());
            });
        });

        return prom->get_future();
    }
};
