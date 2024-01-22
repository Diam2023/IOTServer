#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AliasController : public drogon::HttpController<AliasController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(AliasController::get, "/{2}/{1}", Get); // path is /AliasController/{arg2}/{arg1}
    // METHOD_ADD(AliasController::your_method_name, "/{1}/{2}/list", Get); // path is /AliasController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(AliasController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

        ADD_METHOD_TO(AliasController::newAlias, "/api/alias/new", Put, "LoginFilter");
        ADD_METHOD_TO(AliasController::deleteAlias, "/api/alias/delete", Delete, "LoginFilter");
        ADD_METHOD_TO(AliasController::getAllAlias, "/api/alias/all", Get, "LoginFilter");

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};
