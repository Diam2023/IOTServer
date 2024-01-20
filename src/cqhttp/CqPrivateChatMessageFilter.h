//
// Created by diam on 24-1-20.
//

#pragma once

#include "CqMessageFilter.h"

namespace cq {


    class CqPrivateChatMessageFilter : public virtual CqMessageFilter {

    public:

        CqPrivateChatMessageFilter() = default;

        bool doFilter(const cq::CqMessageData &) override;

        ~CqPrivateChatMessageFilter()
        override = default;

        static CqPrivateChatMessageFilter &getInstance() {
            static CqPrivateChatMessageFilter filter;
            return filter;
        }

    };

}
