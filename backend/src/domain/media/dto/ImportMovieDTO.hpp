#pragma once

#include "CreateMovieDTO.hpp"
#include "../../ExternalSource.hpp"
#include "../Movie.hpp"

struct ImportMovieDTO {
    CreateMovieDTO movie;
    ExternalSource source;
    std::string externalId;

    Movie toDomain(std::string id) const {
        return movie.toDomain(id);
    };
};