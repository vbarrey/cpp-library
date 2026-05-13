#pragma once

#include <crow.h>
#include <memory>
#include "../application/GameService.hpp"

class GameController {
public:
    explicit GameController(std::unique_ptr<GameService> service)
        : service(std::move(service)) {
    }

    template<typename App>
    void registerRoutes(App& app) {

        CROW_ROUTE(app, "/games")
            ([this](const crow::request& req) {
            int page = req.url_params.get("page")
                ? std::stoi(req.url_params.get("page"))
                : 1;

            int limit = req.url_params.get("limit")
                ? std::stoi(req.url_params.get("limit"))
                : 20;

            auto result = service->getPaginatedGames(page, limit);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 500, error.dump() };
            }

            return crow::response{ ((nlohmann::json)result.value()).dump() };
        });

        CROW_ROUTE(app, "/games").methods("POST"_method)
            ([this](const crow::request& req) {
            auto body = nlohmann::json::parse(req.body);
            Game g = body.get<Game>();

            auto result = service->createGame(g);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 400, error.dump() };
            }

            return crow::response{ 201, nlohmann::json(result.value()).dump() };
        });
    }

private:
    std::unique_ptr<GameService> service;
};