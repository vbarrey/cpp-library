#pragma once

#include <memory>
#include <expected>
#include "IBookRepository.hpp"
#include "../domain/DomainError.hpp"
#include "../domain/Result.hpp"

class BookService {
public:
    explicit BookService(std::unique_ptr<IBookRepository> repo)
        : repository(std::move(repo)) {
    }

    Result<std::vector<Book>> getAllBooks() {
        return repository->findAll();
    }

    Result<Book> createBook(const Book& book) {
        auto validation = validate(book);
        if (!validation) {
            return std::unexpected(validation.error());
        }

        return repository->create(book);
    }

private:
    std::unique_ptr<IBookRepository> repository;

    VoidResult validate(const Book& book) {
        if (book.title.empty()) {
            return std::unexpected(DomainError{ "Title cannot be empty" });
        }
        if (book.author.empty()) {
            return std::unexpected(DomainError{ "Author cannot be empty" });
        }
        return {};
    }
};