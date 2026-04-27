#pragma once

#include "IUserRepository.hpp"
#include "../domain/RegisterUserRequest.hpp"
#include "../domain/LoginUserRequest.hpp"
#include "../domain/AuthResponse.hpp"
#include "../security/JwtService.hpp"
#include "../security/PasswordHasher.hpp"
#include <memory>

class AuthService {
public:
    explicit AuthService(std::unique_ptr<IUserRepository> repo)
        : repository(std::move(repo)) {
    }

    Result<User> registerUser(const RegisterUserRequest& request) {
        if (request.username.empty()) {
            return std::unexpected(DomainError{ "Username is required" });
        }

        if (request.email.empty()) {
            return std::unexpected(DomainError{ "Email is required" });
        }

        if (request.password.size() < 8) {
            return std::unexpected(DomainError{ "Password too short" });
        }

        auto existing = repository->findByEmail(request.email);

        if (!existing) {
            return std::unexpected(existing.error());
        }

        if (existing.value().has_value()) {
            return std::unexpected(DomainError{ "Email already exists" });
        }

        auto hashed = PasswordHasher::hash(request.password);

        if (!hashed) {
            return std::unexpected(DomainError{ hashed.error() });
        }

        User user{
            0,
            request.username,
            request.email,
            hashed.value(),
            Role::User
        };

        return repository->create(user);
    }

    Result<AuthResponse> login(const LoginRequest& request) {
        auto userResult = repository->findByEmail(request.email);

        if (!userResult) {
            return std::unexpected(userResult.error());
        }

        auto userOpt = userResult.value();

        if (!userOpt.has_value()) {
            return std::unexpected(
                DomainError{ "Invalid credentials" }
            );
        }

        auto user = userOpt.value();

        auto verified = PasswordHasher::verify(
            request.password,
            user.passwordHash
        );

        if (!verified) {
            return std::unexpected(verified.error());
        }

        if (!verified.value()) {
            return std::unexpected(
                DomainError{ "Invalid credentials" }
            );
        }

        auto token = JwtService::generate(user);

        if (!token) {
            return std::unexpected(token.error());
        }

        return AuthResponse{
            token.value()
        };
    }

private:
    std::unique_ptr<IUserRepository> repository;
};