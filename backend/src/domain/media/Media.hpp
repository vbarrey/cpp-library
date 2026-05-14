#pragma once

#include <string>
#include "MediaType.hpp"
#include "Genre.hpp"

struct Media {
    std::string id;
    MediaType type;
    std::string title;
    std::string description;
    std::string coverUrl;
    std::vector<Genre> genres;
    int rating;
};