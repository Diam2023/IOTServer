//
// Created by diam on 24-1-20.
//

#include "SubscribeApi.h"

#include <drogon/drogon.h>
#include "UserApi.h"
#include "Device.h"
#include "UserDeviceActionMap.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;
using namespace std;

namespace api {

    std::future<std::shared_ptr<std::vector<std::pair<Device, Topic>>>>
    SubscribeApi::listAllSubscribe(const string &token) {

        auto prom = std::make_shared<std::promise<std::shared_ptr<std::vector<std::pair<Device, Topic>>>>>();
        auto resVec = std::make_shared<std::vector<std::pair<Device, Topic>>>();

        drogon::app().getLoop()->runInLoop([prom, resVec, token]() {
            auto dbClientPtr = app().getDbClient();

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }
            Mapper<SubscribeMap> subscribeMapper(dbClientPtr);

            try {
                auto subs = subscribeMapper.findFutureBy(Criteria(SubscribeMap::Cols::_target_user_id,
                                                                  CompareOperator::EQ, uid)).get();
                for (const auto &sub: subs) {
                    // TODO Do not use sync
                    auto t = sub.getTopic(dbClientPtr);
                    auto d = t.getDevice(dbClientPtr);
                    resVec->emplace_back(d, t);
                }
                prom->set_value(resVec);
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
            }
        });

        return prom->get_future();
    }

    std::future<bool> SubscribeApi::subscribeDeviceTopic(const string &token, const string &sn, const string &topic) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, token, sn, topic]() {
            auto dbClientPtr = app().getDbClient();

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }
            Mapper<Device> deviceMapper(dbClientPtr);


            Device device;
            try {
                device = deviceMapper.findFutureOne(
                        Criteria(Device::Cols::_device_sn, CompareOperator::EQ, sn)).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            // Add Topic
            Mapper<Topic> topicMapper(dbClientPtr);
            Topic topicItem;
            topicItem.setTopicName(topic);
            topicItem.setTargetDeviceId(*device.getDeviceId());

            Topic topicRes;
            try {
                topicRes = topicMapper.findFutureOne(
                        Criteria(Topic::Cols::_target_device_id, CompareOperator::EQ, *device.getDeviceId()) &&
                        Criteria(Topic::Cols::_topic_name, CompareOperator::EQ, topic)).get();
            } catch (const DrogonDbException &e) {
                try {
                    topicRes = topicMapper.insertFuture(topicItem).get();
                } catch (const std::exception &e) {
                    prom->set_exception(current_exception());
                    return;
                }
            }

            const auto &topicId = topicRes.getTopicId();

            // Add Subs
            Mapper<SubscribeMap> subscribeMapper(dbClientPtr);
            SubscribeMap subscribeMap;
            subscribeMap.setTargetTopicId(*topicId);
            subscribeMap.setTargetDeviceId(*device.getDeviceId());
            uint32_t uidNum = std::stoul(uid);
            subscribeMap.setTargetUserId(uidNum);

            subscribeMapper.insert(subscribeMap, [prom](const auto &r) {
                prom->set_value(true);
            }, [prom](const auto &e) {
                prom->set_exception(current_exception());
            });
        });

        return prom->get_future();
    }

    std::future<bool>
    SubscribeApi::unsubscribeDeviceTopic(const string &token, const string &sn, const string &topic) {
        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, token, sn, topic]() {
            auto dbClientPtr = app().getDbClient();

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            Mapper<Device> deviceMapper(dbClientPtr);
            Device device;
            try {
                device = deviceMapper.findFutureOne(
                        Criteria(Device::Cols::_device_sn, CompareOperator::EQ, sn)).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            // Find Topic
            Mapper<Topic> topicMapper(dbClientPtr);
            Topic topicRes;
            try {
                topicRes = topicMapper.findFutureOne(
                        Criteria(Topic::Cols::_target_device_id, CompareOperator::EQ, *device.getDeviceId()) &&
                        Criteria(Topic::Cols::_topic_name, CompareOperator::EQ, topic)).get();
            } catch (const DrogonDbException &e) {
                prom->set_exception(current_exception());
                return;
            }

            auto subsMapList = topicRes.getSubscribes(dbClientPtr);
            auto actionList = device.getActions(dbClientPtr);

            if (subsMapList.size() <= 1 && actionList.size() <= 1) {
                // Delete it
                try {
                    topicMapper.deleteFutureBy(
                            Criteria(Topic::Cols::_target_device_id, CompareOperator::EQ, *device.getDeviceId()) &&
                            Criteria(Topic::Cols::_topic_name, CompareOperator::EQ, topic));
                } catch (const DrogonDbException &e) {
                    prom->set_exception(current_exception());
                    return;
                }
            }

            const auto &topicId = topicRes.getTopicId();
            // Remove Subscribe
            Mapper<SubscribeMap> subscribeMapper(dbClientPtr);
            subscribeMapper.deleteBy(
                    Criteria(SubscribeMap::Cols::_target_device_id, CompareOperator::EQ, *device.getDeviceId()) &&
                    Criteria(SubscribeMap::Cols::_target_user_id, CompareOperator::EQ, uid) &&
                    Criteria(SubscribeMap::Cols::_target_topic_id, CompareOperator::EQ, *topicId),
                    [prom](const auto &r) {
                        prom->set_value(r > 0);
                    }, [prom](const auto &e) {
                        prom->set_exception(current_exception());
                    });
        });

        return prom->get_future();
    }
};
