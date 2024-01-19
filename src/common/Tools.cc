//
// Created by diam on 24-1-19.
//

#include "Tools.h"

static std::regex deviceRegex("devices/([[:alnum:]]{16})/([[:alnum:]]*)");

bool isDeviceTopic(const std::string &topic) {
    return regex_match(topic, deviceRegex);
}

std::string getDeviceSerialNumber(const std::string &topic) {
    if (!isDeviceTopic(topic)) {
        return "";
    }

    std::sregex_iterator pos(topic.cbegin(), topic.cend(), deviceRegex);
    return pos->str(1);
}

std::string getDeviceSubTopic(const std::string &topic) {
    if (!isDeviceTopic(topic)) {
        return "";
    }

    std::sregex_iterator pos(topic.cbegin(), topic.cend(), deviceRegex);
    return pos->str(2);
}

std::pair<std::string, std::string> getDeviceSerialNumberAndSubTopic(const std::string &topic) {
    if (!isDeviceTopic(topic)) {
        return std::make_pair("", "");
    }

    std::sregex_iterator pos(topic.cbegin(), topic.cend(), deviceRegex);
    return std::make_pair(pos->str(1), pos->str(2));
}