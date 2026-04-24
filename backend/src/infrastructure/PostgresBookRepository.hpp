#pragma once

#include "../application/IBookRepository.hpp"
#include "../domain/Result.hpp"
#include <pqxx/pqxx>

class PostgresBookRepository : public IBookRepository {
public:
    explicit PostgresBookRepository(const std::string& connStr)
        : connection(connStr) {
    }

    Result<std::vector<Book>> findAll() override {
        pqxx::work txn(connection);

        auto result = txn.exec("SELECT id, title, author FROM books");

        std::vector<Book> books;
        for (const auto& row : result) {
            books.push_back({
                row["id"].as<int>(),
                row["title"].as<std::string>(),
                row["author"].as<std::string>()
                });
        }

        return books;
    }

    Result<Book> create(const Book& book) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(
                "INSERT INTO books (title, author) VALUES ($1, $2) RETURNING id",
                book.title,
                book.author
            );

            txn.commit();

            return Book{
                result[0]["id"].as<int>(),
                book.title,
                book.author
            };
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

private:
    pqxx::connection connection;
};