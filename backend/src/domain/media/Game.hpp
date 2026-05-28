#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Media.hpp"

struct Game {
    Media media;
    std::string developer;
    std::string platform;
    bool multiplayer;
};

inline void to_json(nlohmann::json& j, const Game& g) {
    j = nlohmann::json{
        {"id", g.media.id},
        {"title", g.media.title},
        {"coverUrl", g.media.coverUrl},
        {"description", g.media.description},
        {"rating", g.media.rating},
        {"genres", g.media.genres},
        {"type", "GAME"},
        {"developer", g.developer},
        {"platform", g.platform},
        {"multiplayer", g.multiplayer},
        {"releaseDate", g.media.releaseDate},
        {"createdAt", g.media.createdAt},
        {"updatedAt", g.media. updatedAt}
    };
}

inline void from_json(const nlohmann::json& j, Game& g) {
    j.at("id").get_to(g.media.id);
    j.at("type").get_to(g.media.type);
    j.at("title").get_to(g.media.title);
    j.at("description").get_to(g.media.description);
    j.at("coverUrl").get_to(g.media.coverUrl);
    j.at("rating").get_to(g.media.rating);
    j.at("developer").get_to(g.developer);
    j.at("platform").get_to(g.platform);
    j.at("multiplayer").get_to(g.multiplayer);
    j.at("releaseDate").get_to(g.media.releaseDate);
    j.at("createdAt").get_to(g.media.createdAt);
    j.at("updatedAt").get_to(g.media. updatedAt);
}