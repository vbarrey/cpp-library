#pragma once

#include <crow.h>
#include <memory>
#include "../application/BookService.hpp"

class BookController {
public:
    explicit BookController(std::unique_ptr<BookService> service)
        : service(std::move(service)) {
    }

    void registerRoutes(crow::SimpleApp& app) {

        CROW_ROUTE(app, "/books")
            ([this]() {
            auto result = service->getAllBooks();

            if (!result) {
                return crow::response{ 400, result.error().message };
            }

            return crow::response{ nlohmann::json(result.value()).dump() };
                });

        CROW_ROUTE(app, "/books").methods("POST"_method)
            ([this](const crow::request& req) {

            auto body = nlohmann::json::parse(req.body);
            Book b = body.get<Book>();

            auto result = service->createBook(b);

            if (!result) {
                return crow::response{ 400, result.error().message };
            }

            return crow::response{ 201, nlohmann::json(result.value()).dump() };
                });
    }

private:
    std::unique_ptr<BookService> service;
};