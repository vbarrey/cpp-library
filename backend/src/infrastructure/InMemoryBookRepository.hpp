#pragma once

#include "../application/IBookRepository.hpp"
#include <vector>
#include "../domain/Result.hpp"

class InMemoryBookRepository : public IBookRepository {
public:
    InMemoryBookRepository() {
        books.push_back({ 1, "1984", "George Orwell" });
        books.push_back({ 2, "Dune", "Frank Herbert" });
    }

    Result<std::vector<Book>> findAll() override {
        return books;
    }

    Result<Book> create(const Book& book) override {
        Book b = book;
        b.id = nextId++;
        books.push_back(b);
        return b;
    }

private:
    std::vector<Book> books;
    int nextId = 3;
};