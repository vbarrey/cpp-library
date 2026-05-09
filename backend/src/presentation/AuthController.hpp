#pragma once

#include "../application/AuthService.hpp"

class AuthController {
public:
    explicit AuthController(std::unique_ptr<AuthService> service)
        : service(std::move(service)) {
    }

    template<typename App>
    void registerRoutes(App& app) {
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
                nlohmann::json error = result.error();
                return crow::response{ 400, error.dump() };
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
                nlohmann::json error = result.error();
                return crow::response{ 401, error.dump() };
            }

            nlohmann::json response = {
                {"id", result->id},
                {"username", result->username},
                {"email", result->email},
                {"role", to_string(result->role)}
            };

            return crow::response{
                200,
                response.dump()
            };
                });

        CROW_ROUTE(app, "/auth/check-username")
            ([this](const crow::request& req) {
            auto username = req.url_params.get("username");

            if (!username) {
                return crow::response(
                    400,
                    R"({"error":"missing username"})"
                );
            }

            auto result = service->isUsernameAvailable(username);

            if (!result) {
                nlohmann::json error = result.error();
                return crow::response{ 401, error.dump() };
            }

            nlohmann::json response = { {"available", result.value()} };

            return crow::response{
                200,
                response.dump()
            };
        });
    }

private:
    std::unique_ptr<AuthService> service;
};