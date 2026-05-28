#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Media.hpp"

struct Series {
    Media media;
    std::string director;
    int seasons;
};

inline void to_json(nlohmann::json& j, const Series& s) {
    j = nlohmann::json{
        {"id", s.media.id},
        {"title", s.media.title},
        {"coverUrl", s.media.coverUrl},
        {"description", s.media.description},
        {"genres", s.media.genres},
        {"rating", s.media.rating},
        {"type", "SERIES"},
        {"director", s.director},
        {"seasons", s.seasons},
        {"releaseDate", s.media.releaseDate},
        {"createdAt", s.media.createdAt},
        {"updatedAt", s.media. updatedAt}
    };
}

inline void from_json(const nlohmann::json& j, Series& s) {
    j.at("id").get_to(s.media.id);
    j.at("title").get_to(s.media.title);
    j.at("coverUrl").get_to(s.media.coverUrl);
    j.at("description").get_to(s.media.description);
    j.at("rating").get_to(s.media.rating);
    j.at("type").get_to(s.media.type);
    j.at("director").get_to(s.director);
    j.at("seasons").get_to(s.seasons);
    j.at("releaseDate").get_to(s.media.releaseDate);
    j.at("createdAt").get_to(s.media.createdAt);
    j.at("updatedAt").get_to(s.media. updatedAt);
}