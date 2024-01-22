#pragma once

#include <drogon/WebSocketController.h>
#include <drogon/PubSubService.h>
#include "MqttMessageHandler.h"
#include "Common.h"
#include "LoginFilter.h"

using namespace drogon;

class DeviceMessageNotify : public drogon::WebSocketController<DeviceMessageNotify> {
public:
    void handleNewMessage(const WebSocketConnectionPtr &,
                          std::string &&,
                          const WebSocketMessageType &) override;

    void handleNewConnection(const HttpRequestPtr &,
                             const WebSocketConnectionPtr &) override;

    void handleConnectionClosed(const WebSocketConnectionPtr &) override;

    WS_PATH_LIST_BEGIN
        WS_PATH_ADD("/api/device/notify", "drogon::IntranetIpFilter", "LoginFilter");
    WS_PATH_LIST_END

    static PubSubService<mqtt::MqttData> &getNotifyService() {
        static PubSubService<mqtt::MqttData> notifyService;
        return notifyService;
    }
};

/**
 * To handler Device Message
 */
class DeviceMessageNotifyHandler : public mqtt::MqttMessageHandler {

public:
    DeviceMessageNotifyHandler() = default;

    /**
     * Message Handler
     * @param data
     */
    void handler(const mqtt::MqttData &data) override;

SINGLETON_INTERFACE(DeviceMessageNotifyHandler)
};
