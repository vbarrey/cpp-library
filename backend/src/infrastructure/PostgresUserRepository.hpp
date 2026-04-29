#pragma once

#include "../application/IUserRepository.hpp"
#include "../domain/Result.hpp"
#include "../domain/Role.hpp"
#include <pqxx/pqxx>

class PostgresUserRepository : public IUserRepository {
public :
	explicit PostgresUserRepository(const std::string& conStr) : connection(conStr) {}

    Result<std::optional<User>> findByEmail(const std::string& email) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(
                "SELECT id, username, email, password_hash, role FROM users WHERE email = $1",
                email
            );

            if (result.empty()) {
                return std::nullopt;
            }

            auto row = result[0];

            return User{
                row["id"].as<int>(),
                row["username"].as<std::string>(),
                row["email"].as<std::string>(),
                row["password_hash"].as<std::string>(),
                row["role"].as<std::string>() == "admin" ? Role::Admin : Role::User
            };
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::optional<User>> findByUsername(const std::string username) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(
                "SELECT id, username, email, password_hash, role FROM users WHERE username = $1",
                username
            );

            if (result.empty()) {
                return std::nullopt;
            }


            auto row = result[0];

            return User{
                row["id"].as<int>(),
                row["username"].as<std::string>(),
                row["email"].as<std::string>(),
                row["password_hash"].as<std::string>(),
                row["role"].as<std::string>() == "admin" ? Role::Admin : Role::User
            };
        }
        catch (const std::exception& e) {
                return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<User> create(const User& user) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(
                "INSERT INTO users (username, email, password_hash, role) VALUES($1, $2, $3, $4) RETURNING id",
                user.username,
                user.email,
                user.passwordHash,
                to_string(user.role)
            );

            txn.commit();

            return User{
                result[0]["id"].as<int>(),
                user.username,
                user.email,
                user.passwordHash,
                user.role
            };
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

private :
    pqxx::connection connection;
};