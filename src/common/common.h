//
// Created by diam on 24-1-13.
//

#ifndef IOTSERVER_COMMON_H
#define IOTSERVER_COMMON_H


#include <cstdint>
#include <string_view>

/**
 * Redis Prefix
 */
constexpr std::string_view TOKEN_PREFIX = "TK:";

/**
 * Default permission
 */
const static uint32_t DEFAULT_PERMISSION_ID = 0;

#endif //IOTSERVER_COMMON_H
