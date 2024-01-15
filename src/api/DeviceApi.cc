//
// Created by diam on 24-1-15.
//

#include "DeviceApi.h"

#include <string>

#include <drogon/utils/Utilities.h>
#include <drogon/HttpAppFramework.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::iot_server;
using namespace std;


namespace api {

    std::future<bool> DeviceApi::newDevice(const drogon_model::iot_server::Device &device,
                                           const std::vector<drogon_model::iot_server::Topic> &topics) noexcept(false) {


        auto dbClientPtr = app().getDbClient();

        auto prom = std::make_shared<std::promise<bool>>();


        {

            auto transPtr = dbClientPtr->newTransaction();

            try {

                Mapper<Device> deviceMapper(transPtr);
                auto deviceFuture = deviceMapper.insertFuture(device);
                deviceFuture.get();

                for (auto &topic: topics) {

                    Mapper<Topic> topicMapper(transPtr);
                    auto topicFuture = topicMapper.insertFuture(topic);
                    topicFuture.get();
                }

                prom->set_value(true);
            } catch (const UnexpectedRows &e) {

                // Rollback
                transPtr->rollback();
                LOG_WARN << "Err rollback " << e.what();

                prom->set_exception(std::make_exception_ptr(e));
            } catch (const DrogonDbException &e) {
                prom->set_exception(std::make_exception_ptr(e));
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
            }
        }


        return prom->get_future();
    }

    std::future<bool> DeviceApi::newDevice(const Device &device) noexcept(false) {

        auto dbClientPtr = app().getDbClient();

        auto prom = std::make_shared<std::promise<bool>>();

        Mapper<Device> deviceMapper(dbClientPtr);

        try {
            deviceMapper.insertFuture(device).get();
            // TODO Set To Exception
            prom->set_value(true);
        } catch (const DrogonDbException &e) {
            prom->set_exception(std::make_exception_ptr(e));
        }

        return prom->get_future();
    }

    std::future<bool> DeviceApi::deleteDevice(uint32_t deviceId, bool deleteTopics) noexcept(false) {
        auto dbClientPtr = app().getDbClient();

        auto prom = std::make_shared<std::promise<bool>>();

        auto trans = dbClientPtr->newTransaction();
        Mapper<Device> deviceMapper(trans);
        Mapper<Topic> topicMapper(dbClientPtr);
        try {
            deviceMapper.deleteFutureByPrimaryKey(deviceId).get();

            if (deleteTopics) {
                // Delete All topic
                auto topics = topicMapper.findFutureBy(
                        Criteria(Topic::Cols::_target_device_id, CompareOperator::EQ, deviceId)).get();
                for (auto &topic: topics) {
                    topicMapper.deleteFutureOne(topic).get();
                }
            }

            // TODO Set To Exception
            prom->set_value(true);
        } catch (const DrogonDbException &e) {
            // Roll back!
            trans->rollback();
            prom->set_exception(std::make_exception_ptr(e));
        }

        return prom->get_future();
    }
} // api