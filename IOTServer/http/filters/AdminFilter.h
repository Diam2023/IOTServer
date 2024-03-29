/**
 *
 *  AdminFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class AdminFilter : public HttpFilter<AdminFilter>
{
  public:
    AdminFilter() = default;
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

