#pragma once

#include <crow.h>
#include <memory>
#include "../application/MovieService.hpp"

class MovieController {
public:
    explicit MovieController(std::unique_ptr<MovieService> service)
        : service(std::move(service)) {
    }

    template<typename App>
    void registerRoutes(App& app) {

        CROW_ROUTE(app, "/movies")
            ([this](const crow::request& req) {
            int page = req.url_params.get("page")
                ? std::stoi(req.url_params.get("page"))
                : 1;

            int limit = req.url_params.get("limit")
                ? std::stoi(req.url_params.get("limit"))
                : 20;

            auto result = service->getPaginatedMovies(page, limit);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 500, error.dump() };
            }

            return crow::response{ ((nlohmann::json)result.value()).dump() };
        });

        CROW_ROUTE(app, "/movies").methods("POST"_method)
            ([this](const crow::request& req) {
            auto body = nlohmann::json::parse(req.body);
            Movie m = body.get<Movie>();

            auto result = service->createMovie(m);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 400, error.dump() };
            }

            return crow::response{ 201, nlohmann::json(result.value()).dump() };
        });
    }

private:
    std::unique_ptr<MovieService> service;
};