#pragma once
#include <string>

struct RegisterUserRequest {
    std::string username;
    std::string email;
    std::string password;
};