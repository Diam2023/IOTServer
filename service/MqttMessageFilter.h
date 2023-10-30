//
// Created by 35691 on 10/23/2023.
//

#ifndef IOTSERVER_MQTTMESSAGEFILTER_H
#define IOTSERVER_MQTTMESSAGEFILTER_H

#include <QMqttClient>

namespace mqtt {
    class MqttFilter {
    public:
        virtual bool doFilter(const QMqttTopicName &) = 0;

        ~MqttFilter() = default;
    };

    // 需求：
    // 需要一個過濾類來過濾Topic是否被Mysql收錄，如果收錄了就pass
    // 思考：使用Redis加快查詢速度
    class DataBaseMqttTopicFilter : public virtual MqttFilter, QObject {
    Q_OBJECT;

    private:
        const std::string defaultCacheName = "MqttTopicCache";
    public:

        DataBaseMqttTopicFilter();

        bool doFilter(const QMqttTopicName &) override;

        static DataBaseMqttTopicFilter &getInstance() {
            static DataBaseMqttTopicFilter dbmtf;
            return dbmtf;
        }

        void doSyncUpdate();

        [[noreturn]] void cacheUpdateTask();
    };

} // mqtt

#endif //IOTSERVER_MQTTMESSAGEFILTER_H
