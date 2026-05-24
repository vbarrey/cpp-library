#pragma once

#include "../Genre.hpp"
#include "../MediaType.hpp"
#include "../Media.hpp"

#include <string>
#include <vector>
#include <optional>

struct CreateMediaDTO {
    MediaType type;
    std::string title;
    std::string description;
    std::string coverUrl;
    std::vector<Genre> genres;
    std::optional<std::string> releaseDate;
    double rating;

    Media toDomain(std::string id) const {
        return Media{
            id,
            type,
            title,
            description,
            coverUrl,
            genres,
            rating
        };
    };
};