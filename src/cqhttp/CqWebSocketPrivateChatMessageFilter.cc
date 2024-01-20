//
// Created by diam on 24-1-20.
//

#include "CqWebSocketPrivateChatMessageFilter.h"

bool cq::CqWebSocketPrivateChatMessageFilter::doFilter(const cq::CqMessageData &data) {
    auto messageDataJsonData = data.second["message_type"];
    return messageDataJsonData.asString() == "private";
}
