//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQWEBSOCKETPRIVATECHATMESSAGEHANDLER_H
#define IOTSERVER_CQWEBSOCKETPRIVATECHATMESSAGEHANDLER_H

#include "CqWebSocketMessageHandler.h"

namespace cq {

    class CqWebSocketPrivateChatMessageHandler : public virtual CqWebSocketMessageHandler {

    public:
        CqWebSocketPrivateChatMessageHandler() = default;

        void handler(const cq::CqMessageData &) override;

        ~CqWebSocketPrivateChatMessageHandler() override = default;

        static CqWebSocketPrivateChatMessageHandler &getInstance() {
            static CqWebSocketPrivateChatMessageHandler messageHandler;
            return messageHandler;
        }
    };

} // cq

#endif //IOTSERVER_CQWEBSOCKETPRIVATECHATMESSAGEHANDLER_H
