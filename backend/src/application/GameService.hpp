#pragma once

#include <memory>
#include <expected>
#include "IGameRepository.hpp"
#include "../domain/DomainError.hpp"
#include "../domain/Result.hpp"

class GameService {
public:
    explicit GameService(std::unique_ptr<IGameRepository> repo)
        : repository(std::move(repo)) {
    }

    Result<std::vector<Game>> getAllGames() {
        return repository->findAll();
    }

    Result<PaginatedGames> getPaginatedGames(int page, int limit) {
        int offset = (page - 1) * limit;

        auto games = repository->findPaginated(limit, offset);
        if (!games) return std::unexpected(games.error());

        auto total = repository->count();
        if (!total) return std::unexpected(total.error());

        return PaginatedGames{
            games.value(),
            total.value(),
            page,
            limit
        };
    }

    Result<Game> createGame(const Game& game) {
        auto validation = validate(game);
        if (!validation) {
            return std::unexpected(validation.error());
        }

        return repository->create(game);
    }

private:
    std::unique_ptr<IGameRepository> repository;

    VoidResult validate(const Game& game) {
        if (game.media.title.empty()) {
            return std::unexpected(DomainError{ "Le titre est obligatoire" });
        }
        return {};
    }
};