#pragma once

#include "../application/AuthService.hpp"

class AuthController {
public:
    explicit AuthController(std::unique_ptr<AuthService> service)
        : service(std::move(service)) {
    }

    void registerRoutes(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/auth/register").methods("POST"_method)
            ([this](const crow::request& req) {

            auto body = nlohmann::json::parse(req.body);

            RegisterUserRequest request{
                body["username"],
                body["email"],
                body["password"]
            };

            auto result = service->registerUser(request);

            if (!result) {
                return crow::response{ 400, result.error().message };
            }

            auto user = result.value();

            nlohmann::json response = {
                {"id", user.id},
                {"username", user.username},
                {"email", user.email}
            };

            return crow::response{ 201, response.dump() };
                });

        CROW_ROUTE(app, "/auth/login").methods("POST"_method)
            ([this](const crow::request& req) {
            auto body = nlohmann::json::parse(req.body);

            LoginRequest request{
                body["email"],
                body["password"]
            };

            auto result = service->login(request);

            if (!result) {
                return crow::response{
                    401,
                    result.error().message
                };
            }

            nlohmann::json response = {
                {"token", result->token}
            };

            return crow::response{
                200,
                response.dump()
            };
                });
    }

private:
    std::unique_ptr<AuthService> service;
};