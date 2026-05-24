#pragma once

#include <nlohmann/json.hpp>

#include <optional>
#include <string>
#include <vector>

struct TMDbMovieDTO {
    bool adult;
    std::optional<std::string> backdrop_path;
    std::vector<int> genre_ids;
    int id;
    std::string original_language;
    std::string overview;
    double popularity;
    std::optional<std::string> poster_path;
    std::optional<std::string> release_date;
    std::string title;
    bool video;
    double vote_average;
    int vote_count;
};

inline void from_json(const nlohmann::json& j, TMDbMovieDTO& movie){
    movie.id = j.value("id", 0);
    movie.title =j.value("title", "");
    movie.original_language = j.value("original_language", "");
    movie.overview = j.value("overview", "");
    movie.popularity = j.value("popularity", 0.0);
    movie.vote_average = j.value("vote_average", 0.0);
    movie.vote_count = j.value("vote_count", 0);
    movie.adult = j.value("adult", true);
    movie.video = j.value("video", true);

    if (j.contains("poster_path") && !j["poster_path"].is_null()) {
        movie.poster_path = j["poster_path"].get<std::string>();
    }

    if (j.contains("backdrop_path") && !j["backdrop_path"].is_null()) {
        movie.backdrop_path = j["backdrop_path"].get<std::string>();
    }

    if (j.contains("release_date") && !j["release_date"].is_null()) {
        movie.release_date = j["release_date"].get<std::string>();
    }

    if (j.contains("genre_ids")) {
        movie.genre_ids = j["genre_ids"].get<std::vector<int>>();
    }
}