//
// Created by diam on 24-1-20.
//

#include "CqWebSocketPrivateChatMessageHandler.h"

#include <drogon/drogon.h>

namespace cq {
    void CqWebSocketPrivateChatMessageHandler::handler(const CqMessageData &data) {

        // TODO Private Massage
        LOG_INFO << "private handler: " << data.first << " val: " << data.second.toStyledString();

    }
} // cq