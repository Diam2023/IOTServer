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
const static char *TOKEN_PREFIX = "TK:";

/**
 * Redis QQ ID Cache Prefix
 */
const static char *CQ_PREFIX = "QQ:";


const static char* MQTT_CACHE_NAME = "mqtt:cache";

/**
 * Default permission
 */
const static uint32_t DEFAULT_PERMISSION_LEVEL = 100;

/**
 * Admin must bigger than this value
 */
const static uint32_t DEFAULT_ADMIN_THRESHOLD = 499;

#endif //IOTSERVER_COMMON_H
