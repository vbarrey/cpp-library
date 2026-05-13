#pragma once

#include <vector>
#include "../domain/media/Movie.hpp"
#include "../domain/Result.hpp"

class IMovieRepository {
public:
    // GET
    virtual Result<std::vector<Movie>> findAll() = 0;
    virtual Result<std::vector<Movie>> findPaginated(int limit, int offset) = 0;
    virtual Result<int> count() = 0;

    // POST
    virtual Result<Movie> create(const Movie& movie) = 0;

    virtual ~IMovieRepository() = default;
};