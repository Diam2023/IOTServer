//
// Created by diam on 24-1-20.
//

#pragma once

#include "CqWebSocketMessageFilter.h"

namespace cq {


    class CqWebSocketPrivateChatMessageFilter : public virtual CqWebSocketMessageFilter {

    public:

        CqWebSocketPrivateChatMessageFilter() {};

        bool doFilter(const cq::CqMessageData &) override;


        ~CqWebSocketPrivateChatMessageFilter()
        override {};

        static CqWebSocketPrivateChatMessageFilter &getInstance() {
            static CqWebSocketPrivateChatMessageFilter filter;
            return filter;
        }

    };

}
