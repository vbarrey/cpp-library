#pragma once

#include <vector>
#include "../domain/Book.hpp"
#include "../domain/Result.hpp"

class IBookRepository {
public:
    virtual Result<std::vector<Book>> findAll() = 0;
    virtual Result<Book> create(const Book& book) = 0;

    virtual ~IBookRepository() = default;
};