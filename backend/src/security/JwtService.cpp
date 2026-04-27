#include "JwtService.hpp"
#include <jwt-cpp/traits/nlohmann-json/defaults.h>
#include <jwt-cpp/jwt.h>
#include <stdexcept>

#include "../config/ConfigLoader.hpp"
#include "../config/Config.hpp"

Result<std::string> JwtService::generate(const User& user) {
    auto config = ConfigLoader::load("config.json");
    try {
        auto token = jwt::create()
            .set_type("JWT")
            .set_subject(std::to_string(user.id))
            .set_payload_claim(
                "role",
                jwt::basic_claim<jwt::traits::nlohmann_json>(
                    to_string(user.role)
                )
            )
            .sign(
                jwt::algorithm::hs256{ config.auth.jwt_secret }
            );

        return token;
    }
    catch (const std::exception& e) {
        return std::unexpected(
            DomainError{ e.what() }
        );
    }
}