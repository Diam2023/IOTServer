#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class TopicController : public drogon::HttpController<TopicController> {
public:
    METHOD_LIST_BEGIN

        ADD_METHOD_TO(TopicController::search, "/topic/get", Get, "LoginFilter");

        // ADD_METHOD_TO(TopicController::insert, "/topic/insert", Put, "LoginFilter");

        // ADD_METHOD_TO(TopicController::update, "/topic/update", Patch, "LoginFilter");

        // ADD_METHOD_TO(TopicController::erase, "/topic/delete", Delete, "LoginFilter");

    METHOD_LIST_END

    /**
     * Search topic and return it
     * @param req
     * @param callback
     */
    void search(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Insert to database
     * @param req
     * @param callback
     */
    void insert(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Update topic
     * @param req
     * @param callback
     */
    void update(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    /**
     * Delete target topic
     * @param req
     * @param callback
     */
    void erase(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
