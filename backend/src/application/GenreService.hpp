#pragma once

#include <memory>
#include <expected>

#include "../domain/media/MediaType.hpp"
#include "IGenreRepository.hpp"
#include "../domain/DomainError.hpp"
#include "../domain/Result.hpp"
#include "../domain/Paginated.hpp"

class GenreService {
public:
    explicit GenreService(std::unique_ptr<IGenreRepository> repo)
        : repository(std::move(repo)) {
    }

    Result<std::vector<Genre>> getAllGenres() {
        return repository->findAll();
    }

    Result<std::vector<Genre>> getAllGenresByMediaType(MediaType type) {
        return repository->findAllByMediaType(type);
    }

    Result<Paginated<Genre>> getPaginatedGenres(int page, int limit) {
        int offset = (page - 1) * limit;

        auto genres = repository->findPaginated(limit, offset);
        if (!genres) return std::unexpected(genres.error());

        auto total = repository->count();
        if (!total) return std::unexpected(total.error());

        return Paginated<Genre>{
            genres.value(),
            total.value(),
            page,
            limit
        };
    }

    Result<Paginated<Genre>> getPaginatedGenresByMediaType(MediaType mediaType, int page, int limit) {
        int offset = (page - 1) * limit;

        auto genres = repository->findPaginatedByMediaType(mediaType, limit, offset);
        if (!genres) return std::unexpected(genres.error());

        auto total = repository->count();
        if (!total) return std::unexpected(total.error());

        return Paginated<Genre>{
            genres.value(),
            total.value(),
            page,
            limit
        };
    }

    Result<Genre> createGenre(const Genre& genre) {
        auto validation = validate(genre);
        if (!validation) {
            return std::unexpected(validation.error());
        }

        return repository->create(genre);
    }

private:
    std::unique_ptr<IGenreRepository> repository;

    VoidResult validate(const Genre& genre) {
        if (genre.name.empty()) {
            return std::unexpected(DomainError{ "Le nom est obligatoire" });
        }
        return {};
    }
};