#pragma once

#include <nlohmann/json.hpp>

#include <vector>

template<typename T>
struct TMDbPagedResponse {
    int page;

    int totalPages;

    int totalResults;

    std::vector<T> results;
};

template<typename T>
inline void from_json(const nlohmann::json& j, TMDbPagedResponse<T>& response)
{
    response.page = j.value("page", 0);
    response.totalPages = j.value("total_pages", 0);
    response.totalResults = j.value("total_results", 0);

    if (j.contains("results")) {
        response.results = j["results"].get<std::vector<T>>();
    }
}