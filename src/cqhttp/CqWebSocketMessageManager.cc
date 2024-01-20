//
// Created by diam on 24-1-20.
//

#include "CqWebSocketMessageManager.h"

#include "CqWebSocketPrivateChatMessageFilter.h"
#include "CqWebSocketPrivateChatMessageHandler.h"

void cq::CqWebSocketMessageManager::registerHandler(const cq::CqMessageHandlerType &handler) {
    callbacks.push_back(handler);
}

void cq::CqWebSocketMessageManager::messageIn(const cq::CqMessageData &data) {
    std::lock_guard<std::mutex> lg(messageQueueMutex);
    messageQueue.push(data);
    messageQueueCondVar.notify_one();
}

void cq::CqWebSocketMessageManager::messageIn(cq::CqMessageData &&data) {
    std::lock_guard<std::mutex> lg(messageQueueMutex);
    messageQueue.push(data);
    messageQueueCondVar.notify_one();
}

cq::CqWebSocketMessageManager::CqWebSocketMessageManager() : workerThread(&CqWebSocketMessageManager::worker, this) {
}

void cq::CqWebSocketMessageManager::worker() {

    while (true) {
        cq::CqMessageData data;
        {
            std::unique_lock<std::mutex> ul(messageQueueMutex);
            messageQueueCondVar.wait(ul, [this]() {
                return !messageQueue.empty();
            });
            data = messageQueue.front();
            messageQueue.pop();
        } // Release Lock


        // Call Normal Handlers

        for (const auto &handler: callbacks) {
            handler(data);
        }

        // Do Filter
        if (!cq::CqWebSocketPrivateChatMessageFilter::getInstance().doFilter(data)) {
            // Do Something
            return;
        } else {
            cq::CqWebSocketPrivateChatMessageHandler::getInstance().handler(data);
        }
    }
}
