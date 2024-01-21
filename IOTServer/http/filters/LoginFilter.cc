/**
 *
 *  LoginFilter.cc
 *
 */

#include <drogon/HttpAppFramework.h>
#include "LoginFilter.h"
#include "Common.h"
#include "UserApi.h"

void LoginFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {
    using namespace drogon;
    using namespace drogon::nosql;

    auto &token = req->getHeader("Authorization");

    HttpStatusCode resultCode = kUnknown;

    // Start Verify token
    do {
        if (token.empty()) {
            resultCode = k401Unauthorized;
            break;
        }

        // TODO:1 Verify length or another feature for token

        try {
            auto future = api::UserApi::getUserId(token);
            req->addHeader("uid", future.get());
            resultCode = k200OK;
            // Verify uid exists in mysql
        } catch (const RedisException &e) {
            if (e.code() == RedisErrorCode::kNone) {
                resultCode = k401Unauthorized;
            } else {
                LOG_ERROR << e.what();
                resultCode = k406NotAcceptable;
            }
        }
        catch (const std::exception &e) {
            LOG_ERROR << e.what();
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
