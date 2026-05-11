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

    Result<PaginatedBooks> getPaginatedBooks(int page, int limit) {
        int offset = (page - 1) * limit;

        auto books = repository->findPaginated(limit, offset);
        if (!books) return std::unexpected(books.error());

        auto total = repository->count();
        if (!total) return std::unexpected(total.error());

        return PaginatedBooks{
            books.value(),
            total.value(),
            page,
            limit
        };
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
        if (book.media.title.empty()) {
            return std::unexpected(DomainError{ "Le titre est obligatoire" });
        }
        if (book.author.empty()) {
            return std::unexpected(DomainError{ "L'auteur est obligatoire" });
        }
        return {};
    }
};