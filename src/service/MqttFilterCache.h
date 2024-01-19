//
// Created by diam on 24-1-19.
//

#ifndef IOTSERVER_MQTTFILTERCACHE_H
#define IOTSERVER_MQTTFILTERCACHE_H


#include <thread>
#include <string>
#include <memory>
#include <future>
#include <atomic>

using namespace std::chrono_literals;

class MqttFilterCache {

protected:

    std::chrono::milliseconds updateTime = 500ms;

    std::unique_ptr<std::thread> cacheThread;

    void updateCacheThread();

    std::atomic<bool> exitSignal = false;

public:

    static void clear();

    static void doUpdate();

    void init();

    void stop();

    /**
     * check sn in cache
     * @param sn serialNumber for device
     * @return true if sn exists in cache
     */
    static std::future<bool> findCache(const std::string& sn);

    MqttFilterCache() = default;

    static MqttFilterCache &getInstance() {
        static MqttFilterCache cache;
        return cache;
    }

};


#endif //IOTSERVER_MQTTFILTERCACHE_H
