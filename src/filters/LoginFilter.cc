/**
 *
 *  LoginFilter.cc
 *
 */

#include <drogon/HttpAppFramework.h>
#include "LoginFilter.h"
#include "common.h"

void LoginFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    using namespace drogon;
    using namespace drogon::nosql;

    auto &token = req->getHeader("token");

    HttpStatusCode resultCode = kUnknown;

    // Start Verify token
    do {
        if (token.empty()) {
            resultCode = k401Unauthorized;
            break;
        }

        // TODO:1 Verify length or another feature for token

        auto redisClientPtr = app().getFastRedisClient();
        // if (redisClientPtr)

        try {
            std::string res = redisClientPtr->execCommandSync(
                    [](const RedisResult &r) {
                        return r.asString();
                    },
                    "get %s%s", TOKEN_PREFIX, token
            );
            if (res.empty()) {
                resultCode = k401Unauthorized;
            } else {
                // TODO:2 Verify length or another feature for uuid
                req->addHeader("uuid", res);
                resultCode = k200OK;
            }
        }
        catch (const RedisException &err) {
            // TODO Warning
            LOG_WARN << err.what();
            resultCode = k406NotAcceptable;
        }
        catch (const std::exception &err) {
            LOG_ERROR << err.what();
            resultCode = k503ServiceUnavailable;
        }

    } while (false);

    if (resultCode == k200OK) {
        // Passed
        fccb();
    } else {
        // Check failed
        auto res = drogon::HttpResponse::newHttpResponse();
        res->setStatusCode(resultCode);
        fcb(res);
    }
}
