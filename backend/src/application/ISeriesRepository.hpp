#pragma once

#include <vector>
#include "../domain/media/Series.hpp"
#include "../domain/Result.hpp"

class ISeriesRepository {
public:
    // GET
    virtual Result<std::vector<Series>> findAll() = 0;
    virtual Result<std::vector<Series>> findPaginated(int limit, int offset) = 0;
    virtual Result<int> count() = 0;

    // POST
    virtual Result<Series> create(const Series& Series) = 0;

    virtual ~ISeriesRepository() = default;
};