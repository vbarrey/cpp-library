#pragma once

#include <vector>
#include "../domain/media/dto/CreateMovieDTO.hpp"
#include "../domain/media/dto/ImportMovieDTO.hpp"
#include "../domain/media/Movie.hpp"
#include "../domain/Result.hpp"

class IMovieRepository {
public:
    // GET
    virtual Result<std::vector<Movie>> findAll() = 0;
    virtual Result<std::vector<Movie>> findPaginated(int limit, int offset) = 0;
    virtual Result<int> count() = 0;

    // POST
    virtual Result<Movie> create(const CreateMovieDTO& movie) = 0;
    virtual Result<Movie> externalImport(const ImportMovieDTO& movieImport) = 0;

    virtual ~IMovieRepository() = default;
};