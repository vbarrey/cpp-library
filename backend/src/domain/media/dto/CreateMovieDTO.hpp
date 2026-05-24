#pragma once

#include "CreateMediaDTO.hpp"
#include "../Movie.hpp"

struct CreateMovieDTO {
    CreateMediaDTO media;
    std::string director;
    int durationMinutes;

    Movie toDomain(std::string id) const {
        return Movie{
            media.toDomain(id),
            director,
            durationMinutes
        };
    };
};

inline void to_json(nlohmann::json& j, const CreateMovieDTO& m) {
    j = nlohmann::json{
        {"title", m.media.title},
        {"coverUrl", m.media.coverUrl},
        {"description", m.media.description},
        {"genres", m.media.genres},
        {"rating", m.media.rating},
        {"type", "MOVIE"},
        {"director", m.director},
        {"duration_minutes", m.durationMinutes}
    };
}

inline void from_json(const nlohmann::json& j, CreateMovieDTO& m) {
    j.at("title").get_to(m.media.title);
    j.at("coverUrl").get_to(m.media.coverUrl);
    j.at("description").get_to(m.media.description);
    j.at("rating").get_to(m.media.rating);
    j.at("type").get_to(m.media.type);
    j.at("director").get_to(m.director);
    j.at("duration_minutes").get_to(m.durationMinutes);
}