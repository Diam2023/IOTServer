#include "CqWebsocket.h"

void CqWebsocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    Json::Value tree;
    Json::String err;
    Json::CharReaderBuilder reader;
    std::unique_ptr<Json::CharReader> const json_read(reader.newCharReader());
    json_read->parse(message.c_str(), message.c_str() + message.length(), &tree, &err);

    if ((type == WebSocketMessageType::Text) && !err.empty()) {
        // legal
        LOG_INFO << message;
    }
    // write your application logic here

}

void CqWebsocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    LOG_INFO << "new Req";
    // write your application logic here
}

void CqWebsocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    LOG_INFO << "Req closed";
    // write your application logic here
}
