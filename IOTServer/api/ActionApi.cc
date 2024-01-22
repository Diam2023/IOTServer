//
// Created by diam on 24-1-20.
//

#include "ActionApi.h"


#include <drogon/drogon.h>

#include "UserApi.h"

#include "Device.h"
#include "Topic.h"
#include "SubscribeMap.h"
#include "MqttMessagePublisher.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::iot_server;
using namespace std;

namespace api {

    std::future<bool> ActionApi::addAction(const std::string &token, const std::string &name, const std::string &sn,
                                           const std::string &topic, const std::string &json) {


        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, token, name, sn, topic, json]() {
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
            Mapper<UserDeviceActionMap> userDeviceActionMapper(dbClientPtr);
            UserDeviceActionMap userDeviceActionMap;
            uint32_t uidNum = std::stoul(uid);
            userDeviceActionMap.setTargetUserId(uidNum);
            userDeviceActionMap.setTargetDeviceId(*device.getDeviceId());
            userDeviceActionMap.setActionTargetTopicId(*topicId);
            // TODO Add Name
            userDeviceActionMap.setActionJson(json);
            userDeviceActionMap.setActionName(name);
            userDeviceActionMapper.insert(userDeviceActionMap, [prom](const auto &r) {
                prom->set_value(true);
            }, [prom](const auto &e) {
                prom->set_exception(current_exception());
            });
        });

        return prom->get_future();
    }

    std::future<bool> ActionApi::removeAction(const string &token, const string &action) {
        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, token, action]() {
            auto dbClientPtr = app().getDbClient();

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            Mapper<UserDeviceActionMap> actionMapper(dbClientPtr);

            UserDeviceActionMap actionMap;

            try {
                actionMap = actionMapper.findFutureOne(
                        Criteria(UserDeviceActionMap::Cols::_action_name, CompareOperator::EQ, action)).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            Mapper<Device> deviceMapper(dbClientPtr);
            Device device;
            try {
                device = deviceMapper.findFutureOne(
                        Criteria(Device::Cols::_device_id, CompareOperator::EQ, *actionMap.getTargetDeviceId())).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            // Find Topic
            Mapper<Topic> topicMapper(dbClientPtr);
            Topic topicRes;
            try {
                topicRes = topicMapper.findFutureOne(
                        Criteria(Topic::Cols::_topic_id, CompareOperator::EQ,
                                 *actionMap.getActionTargetTopicId())).get();
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
                            Criteria(Topic::Cols::_topic_id, CompareOperator::EQ, *topicRes.getTopicId()));
                } catch (const DrogonDbException &e) {
                    prom->set_exception(current_exception());
                    return;
                }
            }

            // Remove Action
            actionMapper.deleteBy(
                    Criteria(UserDeviceActionMap::Cols::_action_map_id, CompareOperator::EQ,
                             *actionMap.getActionMapId()),
                    [prom](const auto &r) {
                        prom->set_value(r > 0);
                    }, [prom](const auto &e) {
                        prom->set_exception(current_exception());
                    });
        });

        return prom->get_future();
    }

    std::future<std::shared_ptr<std::vector<std::tuple<Device, Topic, UserDeviceActionMap>>>>
    ActionApi::listAction(const string &token) {

        auto prom = std::make_shared<std::promise<std::shared_ptr<std::vector<std::tuple<Device, Topic, UserDeviceActionMap>>>>>();
        auto resVec = std::make_shared<std::vector<std::tuple<Device, Topic, UserDeviceActionMap>>>();

        drogon::app().getLoop()->runInLoop([prom, resVec, token]() {
            auto dbClientPtr = app().getDbClient();

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }
            Mapper<UserDeviceActionMap> userDeviceActionMapper(dbClientPtr);

            try {
                auto actions = userDeviceActionMapper.findFutureBy(Criteria(UserDeviceActionMap::Cols::_target_user_id,
                                                                            CompareOperator::EQ, uid)).get();
                for (const auto &action: actions) {
                    // TODO Do not use sync
                    auto t = action.getTopic(dbClientPtr);
                    auto d = t.getDevice(dbClientPtr);
                    resVec->emplace_back(d, t, action);
                }
                prom->set_value(resVec);
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
            }
        });

        return prom->get_future();
    }

    static uint8_t qosStringToUint(const std::string &qos) {
        uint8_t qosNum = 0;
        if (qos == "QOS0") {
            qosNum = 0;
        } else if (qos == "QOS1") {
            qosNum = 1;
        } else if (qos == "QOS2") {
            qosNum = 2;
        }
        return qosNum;
    }

    std::future<mqtt::MqttMessagePublisherPackage>
    ActionApi::matchAction(const string &token, const string &action) {
        auto prom = std::make_shared<std::promise<mqtt::MqttMessagePublisherPackage>>();
        drogon::app().getLoop()->runInLoop([prom, token, action]() {
            auto dbClientPtr = app().getDbClient();

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }
            Mapper<UserDeviceActionMap> userDeviceActionMapper(dbClientPtr);

            try {
                auto res = userDeviceActionMapper.findFutureOne(
                        Criteria(UserDeviceActionMap::Cols::_target_user_id, CompareOperator::EQ, uid) &&
                        Criteria(UserDeviceActionMap::Cols::_action_name, CompareOperator::EQ, action)
                ).get();
                auto topic = res.getTopic(dbClientPtr);
                auto device = res.getDevice(dbClientPtr);

                prom->set_value(std::make_tuple(*device.getDeviceSn(), *topic.getTopicName(),
                                                qosStringToUint(*topic.getTopicQos()), *res.getActionJson()));
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
            }
        });
        return prom->get_future();
    }

    void
    ActionApi::launchAction(const string &sn, const string &topic, const string &json) {
        mqtt::MqttMessagePublisher::getInstance().sendMessage({sn, topic, 0, json});
    }
};
