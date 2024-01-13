//
// Created by 35691 on 10/23/2023.
//

#include "MqttMessageFilter.h"

#include <thread>
#include <drogon/drogon.h>
#include <json/value.h>

using namespace std;
using namespace std::chrono_literals;
using namespace drogon;
using namespace drogon::nosql;
using namespace drogon::orm;

namespace mqtt {

    DataBaseMqttTopicFilter::DataBaseMqttTopicFilter() {
        // First Initialize Task
        std::thread task(&DataBaseMqttTopicFilter::cacheUpdateTask, this);
    }

    bool DataBaseMqttTopicFilter::doFilter(const QMqttTopicName &name) {
        std::vector<RedisResult> cacheGetResult;
        try {
            cacheGetResult =
                    app().getRedisClient()->execCommandSync<std::vector<RedisResult>>([](const RedisResult &r) {
                        return r.asArray();

                        // TODO Replace use exists
                    }, "get %s", defaultCacheName.data());
        } catch (const RedisException &err) {
            LOG_ERROR << err.what();
        } catch (const std::exception &e) {
            LOG_ERROR << e.what();
        }

        if (cacheGetResult.empty()) {
            doSyncUpdate();
            if (cacheGetResult.empty()) {
                LOG_DEBUG << "No Mysql Mqtt Topic Name Data Found!!";
                return false;
            }
        }

        if (std::find_if(cacheGetResult.begin(), cacheGetResult.end(), [name](const RedisResult &res) -> bool {
            // 這裏的Name為從真實name 可以直接比較字符串
            return name.name().toStdString() == res.asString();
        }) != cacheGetResult.end()) {
            return true;
        }
        return false;
    }

    [[noreturn]] void DataBaseMqttTopicFilter::cacheUpdateTask() {
        while (true) {
            std::vector<RedisResult> cacheGetResult;
            try {
                cacheGetResult =
                        app().getRedisClient()->execCommandSync<std::vector<RedisResult>>([](const RedisResult &r) {
                            return r.asArray();
                        }, "get %s", defaultCacheName.data());
            } catch (const RedisException &err) {
                LOG_ERROR << err.what();
            } catch (const std::exception &e) {
                LOG_ERROR << e.what();
            }

            if (cacheGetResult.empty()) {
                doSyncUpdate();
            }

            this_thread::sleep_for(10ms);
        }
    }

    void DataBaseMqttTopicFilter::doSyncUpdate() {
        // 更新
        // Start Sync Mysql Data To Cache
        LOG_DEBUG_IF(app().getCustomConfig().get("debug_cache", false).asBool()) << "Cache Update!";
    }

    DataBaseMqttTopicFilter::~DataBaseMqttTopicFilter() = default;

} // mqtt