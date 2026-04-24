#pragma once

#include "Config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

class ConfigLoader {
public:
    static Config load(const std::string& path = "config.json") {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Cannot open config file");
        }

        nlohmann::json j;
        file >> j;

        Config config;

        config.database.host = j["database"]["host"];
        config.database.port = j["database"]["port"];
        config.database.name = j["database"]["name"];
        config.database.user = j["database"]["user"];
        config.database.password = j["database"]["password"];

        return config;
    }
};