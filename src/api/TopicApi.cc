//
// Created by diam on 24-1-16.
//

#include "TopicApi.h"

#include <drogon/HttpAppFramework.h>
#include <drogon/utils/Utilities.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::iot_server;
using namespace std;

namespace api {
    std::future<bool> TopicApi::newTopic(const drogon_model::iot_server::Topic &topic) {
        auto dbClientPtr = app().getDbClient();

        auto prom = std::make_shared<std::promise<bool>>();

        try {
            Mapper<Topic> topicMapper(dbClientPtr);
            auto topicFuture = topicMapper.insertFuture(topic);
            topicFuture.get();

            prom->set_value(true);
        } catch (const DrogonDbException &e) {
            prom->set_exception(std::make_exception_ptr(e));
        } catch (const std::exception &e) {
            prom->set_exception(current_exception());
        }

        return prom->get_future();
    }

    std::future<bool> TopicApi::deleteTopic(uint32_t topicId) noexcept(false) {

        auto dbClientPtr = app().getDbClient();

        auto prom = std::make_shared<std::promise<bool>>();

        try {
            Mapper<Topic> topicMapper(dbClientPtr);
            auto topicFuture = topicMapper.deleteFutureByPrimaryKey(topicId);
            topicFuture.get();

            prom->set_value(true);
        } catch (const DrogonDbException &e) {
            prom->set_exception(std::make_exception_ptr(e));
        } catch (const std::exception &e) {
            prom->set_exception(current_exception());
        }

        return prom->get_future();
    }

    std::future<drogon_model::iot_server::Device> TopicApi::getTargetDevice(uint32_t topicId) {

        auto dbClientPtr = app().getDbClient();

        auto prom = std::make_shared<std::promise<drogon_model::iot_server::Device>>();

        try {
            Mapper<Topic> topicMapper(dbClientPtr);
            Mapper<Device> deviceManager(dbClientPtr);
            auto topic = topicMapper.findFutureByPrimaryKey(topicId).get();
            auto device = deviceManager.findFutureByPrimaryKey(*topic.getTargetDeviceId()).get();

            prom->set_value(device);
        } catch (const DrogonDbException &e) {
            prom->set_exception(std::make_exception_ptr(e));
        } catch (const std::exception &e) {
            prom->set_exception(current_exception());
        }

        return prom->get_future();
    }
} // api