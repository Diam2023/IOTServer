#include "CqWebsocket.h"


#include "CqConnectionPool.h"

void CqWebsocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    Json::Value tree;
    Json::String err;
    Json::CharReaderBuilder reader;
    std::unique_ptr<Json::CharReader> const json_read(reader.newCharReader());
    json_read->parse(message.c_str(), message.c_str() + message.length(), &tree, &err);

    if ((type == WebSocketMessageType::Text) && err.empty()) {
        auto id = cq::CqConnectionPool::getInstance().getId(wsConnPtr);
        // legal
        LOG_INFO << "bot id: " << id;
        LOG_INFO << message;
        // LOAD Filter And Handler
    }
}

void CqWebsocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {

    auto qqId = req->getHeader("X-Self-ID");
    if (qqId.empty()) {
        wsConnPtr->forceClose();
        LOG_INFO << "WS Non QQ ID, Close Connection";
        return;
    }

    LOG_INFO << "WS new bot";
    cq::CqConnectionPool::getInstance().addConnection(qqId, wsConnPtr);
}

void CqWebsocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {

    auto id = cq::CqConnectionPool::getInstance().getId(wsConnPtr);
    if (id.empty()) {
        LOG_WARN << "Close Err WS handle";
    } else {
        LOG_INFO << "WS bot: " << id << " leave";
    }
    cq::CqConnectionPool::getInstance().removeConnection(wsConnPtr);
}
