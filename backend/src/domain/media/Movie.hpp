#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Media.hpp"

struct Movie {
    Media media;
    std::string director;
    int durationMinutes;
};

struct PaginatedMovies {
    std::vector<Movie> data;
    int total;
    int page;
    int limit;
};

inline void to_json(nlohmann::json& j, const Movie& m) {
    j = nlohmann::json{
        {"id", m.media.id},
        {"title", m.media.title},
        {"coverUrl", m.media.coverUrl},
        {"description", m.media.description},
        {"genre", m.media.genre},
        {"rating", m.media.rating},
        {"type", "MOVIE"},
        {"director", m.director},
        {"durationMinutes", m.durationMinutes}
    };
}

inline void from_json(const nlohmann::json& j, Movie& m) {
    j.at("id").get_to(m.media.id);
    j.at("title").get_to(m.media.title);
    j.at("coverUrl").get_to(m.media.coverUrl);
    j.at("description").get_to(m.media.description);
    j.at("genre").get_to(m.media.genre);
    j.at("rating").get_to(m.media.rating);
    j.at("type").get_to(m.media.type);
    j.at("director").get_to(m.director);
    j.at("durationMinutes").get_to(m.durationMinutes);
}