#pragma once

#include <string>
#include "../dto/TMDbMovieDTO.hpp"
#include "../dto/TMDbPagedResponse.hpp"

class TMDbClient {
public:
    explicit TMDbClient(std::string apiKey);

    TMDbPagedResponse<TMDbMovieDTO> discoverMovies(int page);

private:
    std::string apiKey;
};