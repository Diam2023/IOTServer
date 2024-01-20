//
// Created by diam on 24-1-20.
//

#ifndef IOTSERVER_CQUSERAPI_H
#define IOTSERVER_CQUSERAPI_H

#include "common.h"

#include "CqCommand.h"

#include <future>

namespace cq {

    class CqUserApi {

    public:
        static std::future<std::string> getLoginInfo(const std::string &qqId);

        /**
         * Login
         * @param botId
         * @param qqId
         * @param usr
         * @param pwd
         * @return token
         */
        static std::future<std::string>
        login(const std::string &botId, const std::string &qqId, const std::string &usr, const std::string &pwd);

        void logout();


        void addDevice();

        void removeDevice();

        void listDevices();

        void subscribeDeviceMessage();

        void unsubscribeDeviceMessage();

        void listSubscribeDeviceMessage();

        void listDeviceAlias();

        void addDeviceAlias();

        void removeDeviceAlias();

        void aliasCaller();

        void makeAction();

        void deleteAction();

    SINGLETON_INTERFACE(CqUserApi);

    };

} // cq

#endif //IOTSERVER_CQUSERAPI_H
