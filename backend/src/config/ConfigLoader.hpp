#pragma once

#include "Config.hpp"
#include <string>

class ConfigLoader {
public:
    static Config load(const std::string& path);
};