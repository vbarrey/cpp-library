#pragma once

#include <crow.h>
#include <memory>
#include <string>
#include "../application/GenreService.hpp"

class GenreController {
public:
    explicit GenreController(std::unique_ptr<GenreService> service)
        : service(std::move(service)) {
    }

    template<typename App>
    void registerRoutes(App& app) {

        CROW_ROUTE(app, "/genres")
            ([this](const crow::request& req) {
            auto mediaTypeStr = req.url_params.get("mediaType");

            int page = req.url_params.get("page")
                ? std::stoi(req.url_params.get("page"))
                : 1;

            int limit = req.url_params.get("limit")
                ? std::stoi(req.url_params.get("limit"))
                : 20;

            Result<Paginated<Genre>> result;

            if (mediaTypeStr == nullptr) {
                result = service->getPaginatedGenres(page, limit);
            }
            else {
                auto mediaType = mediaTypeFromString(mediaTypeStr);

                if (!mediaType.has_value()) {
                    return crow::response{ 400, "Invalid media type" };
                }

                result = service->getPaginatedGenresByMediaType(mediaType.value(), page, limit);
            }

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 500, error.dump() };
            }

            return crow::response{ ((nlohmann::json)result.value()).dump() };
                });

        CROW_ROUTE(app, "/genres").methods("POST"_method)
            ([this](const crow::request& req) {
            auto body = nlohmann::json::parse(req.body);
            Genre g = body.get<Genre>();

            auto result = service->createGenre(g);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 400, error.dump() };
            }

            return crow::response{ 201, nlohmann::json(result.value()).dump() };
                });
    }

private:
    std::unique_ptr<GenreService> service;
};