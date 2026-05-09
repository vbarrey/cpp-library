#include "ConfigLoader.hpp"
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

Config ConfigLoader::load(const std::string& path) {
    std::ifstream file(path);

    if (!file) {
        throw std::runtime_error("Cannot open config file");
    }

    nlohmann::json j;
    file >> j;

    Config config;

    config.database.host =
        j["database"]["host"].get<std::string>();

    config.database.port =
        j["database"]["port"].get<int>();

    config.database.name =
        j["database"]["name"].get<std::string>();

    config.database.user =
        j["database"]["user"].get<std::string>();

    config.database.password =
        j["database"]["password"].get<std::string>();

    return config;
}