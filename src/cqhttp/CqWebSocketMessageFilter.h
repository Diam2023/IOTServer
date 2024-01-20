//
// Created by diam on 24-1-20.
//

#pragma once

#include <json/json.h>
#include <string>
#include <functional>
#include "CqWebSocketMessageHandler.h"

namespace cq {

    class CqWebSocketMessageFilter {
    public:
        CqWebSocketMessageFilter() = default;

        virtual bool doFilter(const CqMessageData &) = 0;

        virtual ~CqWebSocketMessageFilter() {};
    };

}

