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
    std::string release_date;
    std::string created_at;
    std::string updated_at;
    double rating;
};