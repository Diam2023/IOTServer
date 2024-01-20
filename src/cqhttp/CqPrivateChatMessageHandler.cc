//
// Created by diam on 24-1-20.
//

#include "CqPrivateChatMessageHandler.h"

#include <drogon/drogon.h>

namespace cq {
    void CqPrivateChatMessageHandler::handler(const CqMessageData &data) {

        // TODO Private Massage
        LOG_INFO << "private handler: " << data.first << " val: " << data.second.toStyledString();

        // Get Private id



    }
} // cq