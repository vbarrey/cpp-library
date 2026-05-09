#pragma once
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

struct DomainError {
    std::string description;
    std::optional<std::string> trigger = std::nullopt;
};

inline void to_json(nlohmann::json& j, const DomainError& e) {
    j = nlohmann::json{
        {"description", e.description},
        {"trigger", e.trigger.value_or("")}
    };
}