#include "TMDbClient.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

TMDbClient::TMDbClient(std::string apiKey)
    : apiKey(std::move(apiKey))
{
}

TMDbPagedResponse<TMDbMovieDTO> TMDbClient::discoverMovies(int page)
{
    auto response = cpr::Get(
        cpr::Url{
            "https://api.themoviedb.org/3/discover/movie"
        },

        cpr::Parameters{
            {"api_key", apiKey},
            {"page", std::to_string(page)},
            {"sort_by", "popularity.desc"},
            {"vote_count.gte", "100"},
            {"primary_release_date.gte", "2000-01-01"}
        }
    );

    auto json = nlohmann::json::parse(response.text);

    return json.get<TMDbPagedResponse<TMDbMovieDTO>>();
}