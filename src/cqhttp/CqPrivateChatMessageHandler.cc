//
// Created by diam on 24-1-20.
//

#include "CqPrivateChatMessageHandler.h"

#include <drogon/drogon.h>

namespace cq {
    void CqPrivateChatMessageHandler::handler(const CqMessageData &data) {

        std::string senderId;
        std::string receivedMessage;

        do {


            if (!data.second["sender"]["user_id"].isString() || !data.second["message"].isString()) {
                break;
            }


            senderId = data.second["sender"]["user_id"].asString();
            receivedMessage = data.second["message"].asString();

            if (senderId.empty() || receivedMessage.empty()) {
                break;
            }

            // TODO Call login or another here
            LOG_INFO << "private message received: " << data.first << " sender: " << senderId << " msg: "
                     << receivedMessage;

        } while (false);

        // Get Private id
    }
} // cq