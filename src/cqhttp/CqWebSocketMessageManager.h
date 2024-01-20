//
// Created by diam on 24-1-20.
//

#pragma once

#include "CqWebSocketMessageHandler.h"

#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace cq {
    /**
     * To Filter, Handler WS Message
     */
    class CqWebSocketMessageManager {

    private:
        /**
         * Callbacks
         */
        std::vector<CqMessageHandlerType> callbacks;

        // Message Queue
        std::queue<CqMessageData> messageQueue;
        std::mutex messageQueueMutex;
        std::condition_variable messageQueueCondVar;

        std::thread workerThread;

    public:

        CqWebSocketMessageManager();

        void messageIn(const cq::CqMessageData &data);

        void messageIn(cq::CqMessageData &&data);

        /**
         * Do Not Use This Api in multi-thread
         * @param handler
         */
        void registerHandler(const CqMessageHandlerType &handler);

        // Do not call this
        [[noreturn]] void worker();

        static CqWebSocketMessageManager &getInstance() {
            static CqWebSocketMessageManager manager;
            return manager;
        }
    };

}
