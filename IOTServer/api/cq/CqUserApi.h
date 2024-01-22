//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQUSERAPI_H
#define IOTSERVER_CQUSERAPI_H

#include "Common.h"

#include "CqCommand.h"

#include <future>

namespace cq {

    class CqUserApi {

    public:

        /**
         * Only CQ Get Logged in token
         * @param qqId
         * @return
         */
        static std::future<std::string> getCqLoginInfo(const std::string &qqId);

        /**
         * Only CQ Login
         * @param botId
         * @param qqId
         * @param usr
         * @param pwd
         * @return token
         */
        static std::future<std::string>
        cqLogin(const std::string &botId, const std::string &qqId, const std::string &usr, const std::string &pwd);

        static std::future<bool> cqLogout(const std::string &qqId);

    SINGLETON_INTERFACE(CqUserApi);

    };

} // cq

#endif //IOTSERVER_CQUSERAPI_H
