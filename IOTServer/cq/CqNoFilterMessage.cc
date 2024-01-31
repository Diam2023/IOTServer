//
// Created by diam on 24-1-20.
//

#include "CqNoFilterMessage.h"

#include <drogon/drogon.h>

void cq::CqNoFilterMessage::handler(const cq::CqMessageData &data) {
    // display no filter message
    LOG_INFO << "No Filter Message: " << data.first << " json: " << data.second.toStyledString();
}
