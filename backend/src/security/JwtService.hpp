#pragma once

#include "../domain/User.hpp"
#include "../domain/Result.hpp"

class JwtService {
public:
    static Result<std::string> generate(const User& user);
};