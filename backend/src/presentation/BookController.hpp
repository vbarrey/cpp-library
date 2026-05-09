#pragma once

#include <crow.h>
#include <memory>
#include "../application/BookService.hpp"

class BookController {
public:
    explicit BookController(std::unique_ptr<BookService> service)
        : service(std::move(service)) {
    }

    template<typename App>
    void registerRoutes(App& app) {

        CROW_ROUTE(app, "/books")
            ([this](const crow::request& req) {
                int page = req.url_params.get("page")
                    ? std::stoi(req.url_params.get("page"))
                    : 1;

                int limit = req.url_params.get("limit")
                    ? std::stoi(req.url_params.get("limit"))
                    : 20;

                auto result = service->getPaginatedBooks(page, limit);

                if (!result) {
                    nlohmann::json error = result.error();
                    return crow::response{ 500, error.dump() };
                }

                nlohmann::json res = {
                    {"data", result->data},
                    {"total", result->total},
                    {"page", result->page},
                    {"limit", result->limit}
                };

                return crow::response{ res.dump() };
            });

        CROW_ROUTE(app, "/books").methods("POST"_method)
            ([this](const crow::request& req) {
                auto body = nlohmann::json::parse(req.body);
                Book b = body.get<Book>();

                auto result = service->createBook(b);

                if (!result) {
                    nlohmann::json error = result.error();
                    return crow::response{ 400, error.dump()};
                }

                return crow::response{ 201, nlohmann::json(result.value()).dump() };
            });
    }

private:
    std::unique_ptr<BookService> service;
};