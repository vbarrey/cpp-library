#pragma once

#include "../domain/User.hpp"
#include "../domain/Result.hpp"
#include <optional>

class IUserRepository {
public:
    virtual Result<User> create(const User& user) = 0;
    virtual Result<std::optional<User>> findByEmail(const std::string& email) = 0;

    virtual ~IUserRepository() = default;
};