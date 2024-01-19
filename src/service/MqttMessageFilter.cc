//
// Created by 35691 on 10/23/2023.
//

#include "MqttMessageFilter.h"

#include <drogon/drogon.h>
#include "MqttFilterCache.h"
#include "Tools.h"

using namespace drogon::nosql;

namespace mqtt {

    DataBaseMqttTopicFilter::DataBaseMqttTopicFilter() {
        MqttFilterCache::getInstance().init();
    }

    bool DataBaseMqttTopicFilter::doFilter(const MqttData &data) {

        bool result = false;

        auto serialNumber = getDeviceSerialNumber(data.first.name().toStdString());
        if (serialNumber.empty()) {
            return result;
        }

        auto future = MqttFilterCache::findCache(serialNumber);

        try {
            result = future.get();
        } catch (const RedisException &e) {
            LOG_WARN << "Redis Exception: " << e.what();
            return result;
        }

        return result;
    }

    DataBaseMqttTopicFilter::~DataBaseMqttTopicFilter() = default;

} // mqtt