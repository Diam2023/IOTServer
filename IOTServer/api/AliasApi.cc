//
// Created by diam on 24-1-20.
//

#include "AliasApi.h"

#include <drogon/drogon.h>
#include "UserApi.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;
using namespace std;

namespace api {


    std::future<bool> AliasApi::addAlias(const string &token, const string &sn, const string &alias) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, token, sn, alias]() {

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            auto dbClientPtr = app().getDbClient();

            Mapper<Device> deviceMapper(dbClientPtr);
            Device device;
            try {
                device = deviceMapper.findFutureOne(
                        Criteria(Device::Cols::_device_sn, CompareOperator::EQ, sn)).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            Mapper<UserDeviceAliasMap> aliasMapper(dbClientPtr);

            uint32_t uidNum = std::stoul(uid);
            UserDeviceAliasMap aliasMap;
            aliasMap.setTargetUserId(uidNum);
            aliasMap.setTargetDeviceId(*device.getDeviceId());
            aliasMap.setAliasName(alias);

            try {
                aliasMapper.insertFuture(aliasMap).get();
                prom->set_value(true);
            } catch (const std::exception &e) {
                prom->set_exception(std::current_exception());
            }
        });

        return prom->get_future();
    }

    std::future<bool> AliasApi::removeAlias(const string &token, const string &alias) {

        auto prom = std::make_shared<std::promise<bool>>();

        drogon::app().getLoop()->runInLoop([prom, token, alias]() {

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            auto dbClientPtr = app().getDbClient();

            Mapper<UserDeviceAliasMap> aliasMapper(dbClientPtr);
            try {
                auto res = aliasMapper.deleteFutureBy(
                        Criteria(UserDeviceAliasMap::Cols::_target_user_id, CompareOperator::EQ, uid) &&
                        Criteria(UserDeviceAliasMap::Cols::_alias_name, CompareOperator::EQ, alias)).get();
                prom->set_value(res > 0);
            } catch (const std::exception &e) {
                prom->set_exception(std::current_exception());
            }
        });

        return prom->get_future();
    }

    std::future<std::shared_ptr<std::vector<std::pair<Device, UserDeviceAliasMap>>>>
    AliasApi::listAlias(const string &token) {

        auto prom = std::make_shared<std::promise<std::shared_ptr<std::vector<std::pair<Device, UserDeviceAliasMap>>>>>();
        auto resVec = std::make_shared<std::vector<std::pair<Device, UserDeviceAliasMap>>>();

        drogon::app().getLoop()->runInLoop([prom, token, resVec]() {

            std::string uid;
            try {
                uid = api::UserApi::getUserId(token).get();
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
                return;
            }

            auto dbClientPtr = app().getDbClient();

            Mapper<UserDeviceAliasMap> aliasMapper(dbClientPtr);
            try {

                auto aliasList = aliasMapper.findFutureBy(
                        Criteria(UserDeviceAliasMap::Cols::_target_user_id, CompareOperator::EQ, uid)).get();

                for (const auto &alias: aliasList) {
                    auto device = alias.getDevice(dbClientPtr);
                    resVec->emplace_back(device, alias);
                }
                prom->set_value(resVec);
            } catch (const std::exception &e) {
                prom->set_exception(current_exception());
            }
        });

        return prom->get_future();
    }

};