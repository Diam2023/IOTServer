//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQPRIVATECHATMESSAGEHANDLER_H
#define IOTSERVER_CQPRIVATECHATMESSAGEHANDLER_H

#include "CqMessageHandler.h"

namespace cq {

    class CqPrivateChatMessageHandler : public virtual CqMessageHandler {

    public:
        CqPrivateChatMessageHandler() = default;

        void handler(const cq::CqMessageData &) override;

        ~CqPrivateChatMessageHandler() override = default;

        static CqPrivateChatMessageHandler &getInstance() {
            static CqPrivateChatMessageHandler messageHandler;
            return messageHandler;
        }
    };

} // cq

#endif //IOTSERVER_CQPRIVATECHATMESSAGEHANDLER_H
