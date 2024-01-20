//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQNOFILTERMESSAGE_H
#define IOTSERVER_CQNOFILTERMESSAGE_H

#include "common.h"

#include "CqMessageHandler.h"

namespace cq {


    class CqNoFilterMessage : public virtual CqMessageHandler {

    public:
        CqNoFilterMessage() = default;

        void handler(const cq::CqMessageData &) override;

    SINGLETON_INTERFACE(CqNoFilterMessage);
    };
};


#endif //IOTSERVER_CQNOFILTERMESSAGE_H
