#pragma once

#include <vector>
#include "../domain/media/Book.hpp"
#include "../domain/Result.hpp"

class IBookRepository {
public:
    // GET
    virtual Result<std::vector<Book>> findAll() = 0;
    virtual Result<std::vector<Book>> findPaginated(int limit, int offset) = 0;
    virtual Result<int> count() = 0;

    // POST
    virtual Result<Book> create(const Book& book) = 0;

    virtual ~IBookRepository() = default;
};