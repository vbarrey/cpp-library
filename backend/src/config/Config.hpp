#pragma once
#include <string>

struct DatabaseConfig {
    std::string host;
    int port;
    std::string name;
    std::string user;
    std::string password;
};

struct AuthConfig {
    std::string jwt_secret;
};

struct Config {
    DatabaseConfig database;
    AuthConfig auth;
};