#pragma once

#include <memory>
#include <expected>
#include "IMovieRepository.hpp"
#include "../domain/DomainError.hpp"
#include "../domain/Result.hpp"
#include "../domain/Paginated.hpp"

class MovieService {
public:
    explicit MovieService(std::unique_ptr<IMovieRepository> repo)
        : repository(std::move(repo)) {
    }

    Result<std::vector<Movie>> getAllMovies() {
        return repository->findAll();
    }

    Result<Paginated<Movie>> getPaginatedMovies(int page, int limit) {
        int offset = (page - 1) * limit;

        auto movies = repository->findPaginated(limit, offset);
        if (!movies) return std::unexpected(movies.error());

        auto total = repository->count();
        if (!total) return std::unexpected(total.error());

        return Paginated<Movie>{
            movies.value(),
            total.value(),
            page,
            limit
        };
    }

    Result<Movie> createMovie(const Movie& movie) {
        auto validation = validate(movie);
        if (!validation) {
            return std::unexpected(validation.error());
        }

        return repository->create(movie);
    }

private:
    std::unique_ptr<IMovieRepository> repository;

    VoidResult validate(const Movie& movie) {
        if (movie.media.title.empty()) {
            return std::unexpected(DomainError{ "Le titre est obligatoire" });
        }
        return {};
    }
};