#pragma once

#include <vector>
#include "../domain/media/Game.hpp"
#include "../domain/Result.hpp"

class IGameRepository {
public:
    // GET
    virtual Result<std::vector<Game>> findAll() = 0;
    virtual Result<std::vector<Game>> findPaginated(int limit, int offset) = 0;
    virtual Result<int> count() = 0;

    // POST
    virtual Result<Game> create(const Game& game) = 0;

    virtual ~IGameRepository() = default;
};