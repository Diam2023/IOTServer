//
// Created by diam on 24-1-19.
//

#ifndef IOTSERVER_TOOLS_H
#define IOTSERVER_TOOLS_H

#include <regex>
#include <string>

bool isDeviceTopic(const std::string &topic);

std::string getDeviceSerialNumber(const std::string &topic);

std::string getDeviceSubTopic(const std::string &topic);

std::pair<std::string, std::string> getDeviceSerialNumberAndSubTopic(const std::string &topic);

#endif //IOTSERVER_TOOLS_H
