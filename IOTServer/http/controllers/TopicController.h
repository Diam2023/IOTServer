#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TopicController : public drogon::HttpController<TopicController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(TopicController::newTopic, "/topic/new", Put, "LoginFilter", "AdminFilter");
        ADD_METHOD_TO(TopicController::deleteTopic, "/topic/delete", Delete, "LoginFilter", "AdminFilter");
        ADD_METHOD_TO(TopicController::getAllTopic, "/topic/all", Get, "LoginFilter");

    METHOD_LIST_END

    /**
     * Create New Topic To Topic Table
     * @param req
     * @param callback
     */
    void newTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Delete Topic From Topic Table
     * @param req
     * @param callback
     */
    void deleteTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Get All Topic For Device
     * @param req
     * @param callback
     */
    void getAllTopic(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
