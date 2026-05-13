#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "Media.hpp"

struct Game {
    Media media;
    std::string developer;
    std::string platform;
    int multiplayer;
};

struct PaginatedGames {
    std::vector<Game> data;
    int total;
    int page;
    int limit;
};

inline void to_json(nlohmann::json& j, const Game& g) {
    j = nlohmann::json{
        {"id", g.media.id},
        {"title", g.media.title},
        {"coverUrl", g.media.coverUrl},
        {"description", g.media.description},
        {"rating", g.media.rating},
        {"genre", g.media.genre},
        {"type", "GAME"},
        {"developer", g.developer},
        {"platform", g.platform},
        {"multiplayer", g.multiplayer},
    };
}

inline void from_json(const nlohmann::json& j, Game& g) {
    j.at("id").get_to(g.media.id);
    j.at("type").get_to(g.media.type);
    j.at("title").get_to(g.media.title);
    j.at("description").get_to(g.media.description);
    j.at("coverUrl").get_to(g.media.coverUrl);
    j.at("genre").get_to(g.media.genre);
    j.at("rating").get_to(g.media.rating);
    j.at("developer").get_to(g.developer);
    j.at("platform").get_to(g.platform);
    j.at("multiplayer").get_to(g.multiplayer);
}