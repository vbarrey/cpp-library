#pragma once

#include "../../../domain/media/dto/CreateMovieDTO.hpp"
#include "../dto/TMDbMovieDTO.hpp"

class TMDbMovieMapper {
public:
    static CreateMovieDTO fromDMDb(const TMDbMovieDTO& dto);
};