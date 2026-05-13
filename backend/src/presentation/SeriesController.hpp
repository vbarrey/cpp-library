#pragma once

#include <crow.h>
#include <memory>
#include "../application/SeriesService.hpp"

class SeriesController {
public:
    explicit SeriesController(std::unique_ptr<SeriesService> service)
        : service(std::move(service)) {
    }

    template<typename App>
    void registerRoutes(App& app) {

        CROW_ROUTE(app, "/series")
            ([this](const crow::request& req) {
            int page = req.url_params.get("page")
                ? std::stoi(req.url_params.get("page"))
                : 1;

            int limit = req.url_params.get("limit")
                ? std::stoi(req.url_params.get("limit"))
                : 20;

            auto result = service->getPaginatedSeries(page, limit);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 500, error.dump() };
            }

            return crow::response{ ((nlohmann::json)result.value()).dump() };
        });

        CROW_ROUTE(app, "/series").methods("POST"_method)
            ([this](const crow::request& req) {
            auto body = nlohmann::json::parse(req.body);
            Series s = body.get<Series>();

            auto result = service->createSeries(s);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 400, error.dump() };
            }

            return crow::response{ 201, nlohmann::json(result.value()).dump() };
        });
    }

private:
    std::unique_ptr<SeriesService> service;
};