#pragma once

#include <string>
#include "../domain/Role.hpp"

struct AuthResponse {
    int id;
    std::string username;
    std::string email;
    Role role;
};