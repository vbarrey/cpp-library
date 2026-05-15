#pragma once

#include <vector>
#include "../domain/media/Genre.hpp"
#include "../domain/media/MediaType.hpp"
#include "../domain/Result.hpp"

class IGenreRepository {
public:
    // GET 
    virtual Result<std::vector<Genre>> findAll() = 0;
    virtual Result<std::vector<Genre>> findPaginated(int limit, int offset) = 0;
    virtual Result<int> count() = 0;

    // GET BY MEDIA
    virtual Result<std::vector<Genre>> findAllByMediaType(MediaType type) = 0;
    virtual Result<std::vector<Genre>> findPaginatedByMediaType(MediaType type, int limit, int offset) = 0;
    
    // POST
    virtual Result<Genre> create(const Genre& genre) = 0;

    virtual ~IGenreRepository() = default;
};