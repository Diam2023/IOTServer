//
// Created by 35691 on 10/23/2023.
//

#ifndef IOTSERVER_MQTTMESSAGEFILTER_H
#define IOTSERVER_MQTTMESSAGEFILTER_H

#include <QMqttClient>
#include "MqttClient.h"

namespace mqtt {
    class MqttFilter : public QObject {
    Q_OBJECT;
    public:
        virtual bool doFilter(const MqttData &) = 0;

        ~MqttFilter() override = default;
    };

    // 需求：
    // 需要一個過濾類來過濾Topic是否被Mysql收錄，如果收錄了就pass
    // 思考：使用Redis加快查詢速度
    class DataBaseMqttTopicFilter : public virtual MqttFilter {
    Q_OBJECT;

    private:
        const std::string defaultCacheName = "MqttTopicCache";
    public:

        DataBaseMqttTopicFilter();

        // Search Redis if exist
        bool doFilter(const MqttData &) override;

        static DataBaseMqttTopicFilter &getInstance() {
            static DataBaseMqttTopicFilter dbmtf;
            return dbmtf;
        }

        ~DataBaseMqttTopicFilter() override;
    };
} // mqtt

#endif //IOTSERVER_MQTTMESSAGEFILTER_H
