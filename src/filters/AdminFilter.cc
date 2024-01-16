/**
 *
 *  AdminFilter.cc
 *
 */

#include "AdminFilter.h"

#include <drogon/HttpAppFramework.h>

#include "UserApi.h"
#include "common.h"

using namespace drogon;
using namespace drogon::nosql;
using namespace drogon::orm;

void AdminFilter::doFilter(const HttpRequestPtr &req,
                           FilterCallback &&fcb,
                           FilterChainCallback &&fccb) {

    // Request Login Filter
    HttpStatusCode resultCode = kUnknown;

    do {

        auto &token = req->getHeader("Authorization");
        if (token.empty()) {
            resultCode = k203NonAuthoritativeInformation;
            break;
        }

        try {
            auto level = api::UserApi::getUserPermissionLevel(token).get();
            if (level > DEFAULT_ADMIN_THRESHOLD) {
                fccb();
                return;
            } else {
                resultCode = k401Unauthorized;
            }
        } catch (const UnexpectedRows &e) {
            resultCode = k401Unauthorized;
            // Not found
        } catch (const RedisException &e) {
            resultCode = k401Unauthorized;
            // Need Login
        } catch (const std::exception &e) {
            resultCode = k500InternalServerError;
        }

    } while (false);

    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(resultCode);
    fcb(res);
}
