//
// Created by diam on 24-1-19.
//

#ifndef IOTSERVER_CQCONNECTIONPOOL_H
#define IOTSERVER_CQCONNECTIONPOOL_H


#include <drogon/WebSocketConnection.h>
#include <condition_variable>

namespace cq {

    // Bot id and Bot ws ptr
    using CqConnection = std::pair<std::string, drogon::WebSocketConnectionPtr>;


    /**
     * CqHttp WebSocket Connection Pool
     */
    class CqConnectionPool {

    private:

        std::mutex poolMutex;

        std::condition_variable poolCondVar;

        std::vector<CqConnection> connectionPool;

    public:

        CqConnectionPool() = default;

        void addConnection(const std::string &, const drogon::WebSocketConnectionPtr &);

        void removeConnection(const drogon::WebSocketConnectionPtr &);

        std::string getId(const drogon::WebSocketConnectionPtr &);

        static CqConnectionPool &getInstance() {
            static CqConnectionPool pool;
            return pool;
        }
    };

} // cq

#endif //IOTSERVER_CQCONNECTIONPOOL_H
