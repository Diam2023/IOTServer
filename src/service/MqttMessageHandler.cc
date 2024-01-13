//
// Created by diam on 24-1-9.
//

#include "MqttMessageHandler.h"
#include <drogon/drogon.h>


namespace mqtt {
    void MqttMessageHandler::messageHandler(const QByteArray &message, const QMqttTopicName &topic) {
        // Update to Mysql And Redis


        // First:  Search Redis Topic List.
        // Second: Update To Redis And Mysql If Exist.
        auto redisClient = drogon::app().getFastRedisClient();

        redisClient->
                execCommandAsync(
                [](const drogon::nosql::RedisResult &r) {
                    // TODO item
                    do {
                        if (!r.isNil()) {
                            break;
                        }

                        auto resArr = r.asArray();
                        if (resArr.empty()) {
                            break;
                        }

                        for (const auto &topicItem: resArr) {

                        }

                    } while (false);
                }, [](
                        const std::exception &err
                ) {
                    std::cerr << err.

                            what()

                              <<
                              std::endl;
                    // TODO ?
                }, "get %s", "?"
        );

    }
} // mqtt