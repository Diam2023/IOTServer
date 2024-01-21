//
// Created by diam on 24-1-19.
//

#include "MqttFilterCache.h"

#include <drogon/HttpAppFramework.h>

#include "Device.h"
#include "Common.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon::nosql;
using namespace drogon_model::iot_server;
using namespace std;

void MqttFilterCache::doUpdate() {
    auto clientPtr = app().getDbClient();
    Mapper<Device> deviceMapper(clientPtr);
    deviceMapper.findAll([](const auto &devices) {
        auto redisClientPtr = app().getRedisClient();
        for (const Device &device: devices) {
            const auto &sn = device.getDeviceSn();
            redisClientPtr->execCommandAsync([redisClientPtr, sn](const RedisResult &result) {
                if ((result.type() == RedisResultType::kInteger) && (result.asInteger() == 0)) {
                    // Append
                    redisClientPtr->execCommandAsync([sn](const RedisResult &result) {
                        if ((result.type() == drogon::nosql::RedisResultType::kInteger) && (result.asInteger() == 1)) {
                            // successful
                        } else {
                            LOG_WARN << "Err add cache";
                        }
                    }, [](const auto &e) {
                        LOG_WARN << "Err add cache";

                    }, "sadd %s %s", MQTT_CACHE_NAME, sn->c_str());
                }
            }, [](auto &e) {
                LOG_WARN << "Err add cache";

            }, "sismember %s %s", MQTT_CACHE_NAME, sn->c_str());
        }
    }, [](const auto &e) {
        LOG_WARN << "doUpdate Exception";
    });
}

void MqttFilterCache::updateCacheThread() {
    while (true) {
        auto loop = drogon::app().getLoop();
        loop->queueInLoop(doUpdate);
        std::this_thread::sleep_for(updateTime);
        if (exitSignal) {
            break;
        }
    }
}

void MqttFilterCache::init() {
    exitSignal = false;
    cacheThread = std::make_unique<std::thread>(&MqttFilterCache::updateCacheThread, this);
}

void MqttFilterCache::clear() {
    auto loop = drogon::app().getLoop();
    loop->queueInLoop([]() {
        auto redisClientPtr = app().getRedisClient();
        redisClientPtr->execCommandAsync([](const RedisResult &result) {
            if ((result.type() == drogon::nosql::RedisResultType::kInteger) && (result.asInteger() == 1)) {
                // successful
            }
        }, [](const auto &e) {
            LOG_WARN << "Err del cache";
        }, "del %s", MQTT_CACHE_NAME);
    });
}

void MqttFilterCache::stop() {
    if (cacheThread) {
        exitSignal = true;
        if (cacheThread->joinable()) {
            cacheThread->join();
        }
    }
}

std::future<bool> MqttFilterCache::findCache(const string &sn) {
    auto prom = std::make_shared<std::promise<bool>>();

    auto loop = drogon::app().getLoop();
    loop->queueInLoop([prom, sn]() {
        auto redisClientPtr = app().getRedisClient();
        redisClientPtr->execCommandAsync([prom](const RedisResult &result) {
            if ((result.type() == drogon::nosql::RedisResultType::kInteger) && (result.asInteger() == 1)) {
                // successful
                prom->set_value(true);
            } else {
                prom->set_value(false);
            }
        }, [prom](const auto &e) {
            prom->set_exception(std::make_exception_ptr(e));
        }, "sismember %s %s", MQTT_CACHE_NAME, sn.c_str());
    });
    return prom->get_future();
}
