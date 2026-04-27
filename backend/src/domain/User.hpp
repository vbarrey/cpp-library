#pragma once

#include <string>
#include "Role.hpp"

struct User {
    int id;
    std::string username;
    std::string email;
    std::string passwordHash;
    Role role;
};