#pragma once

#include <expected>
#include "DomainError.hpp"

template<typename T>
struct Paginated {
    std::vector<T> data;
    int total;
    int page;
    int limit;
};

template<typename T>
inline void to_json(nlohmann::json& j, const Paginated<T>& paginated) {
    j = nlohmann::json{
        {"data", paginated.data},
        {"total", paginated.total},
        {"page", paginated.page},
        {"limit", paginated.limit}
    };
}