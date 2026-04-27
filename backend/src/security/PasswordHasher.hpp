#pragma once

#include <string>
#include "../domain/Result.hpp"

class PasswordHasher {
public:
    static Result<std::string> hash(const std::string& password);
    static Result<bool> verify(
        const std::string& password,
        const std::string& hash
    );
};