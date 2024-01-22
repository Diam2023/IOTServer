#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ActionController : public drogon::HttpController<ActionController>
{
  public:
    METHOD_LIST_BEGIN

//        ADD_METHOD_TO(ActionController::newAction, "/api/action/new", Put, "LoginFilter");
//        ADD_METHOD_TO(ActionController::deleteAction, "/api/action/delete", Delete, "LoginFilter");
//        ADD_METHOD_TO(ActionController::getAllAction, "/api/action/all", Get, "LoginFilter");

    METHOD_LIST_END
};
