#pragma once
#include <string>

struct DatabaseConfig {
    std::string host;
    int port;
    std::string name;
    std::string user;
    std::string password;
};

struct TMDBConfig {
    std::string api_key;
};

struct Config {
    DatabaseConfig database;
    TMDBConfig tmdb;

    std::string getPostgresConnexionStr() {
        return "dbname=" + database.name +
            " user=" + database.user +
            " password=" + database.password +
            " host=" + database.host +
            " port=" + std::to_string(database.port);
    }
};