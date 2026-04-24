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
        try {
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
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Book>> findPaginated(int limit, int offset) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(
                "SELECT id, title, author FROM books ORDER BY id LIMIT $1 OFFSET $2",
                limit,
                offset
            );

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
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<int> count() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec("SELECT COUNT(id) FROM books");

            return result[0][0].as<int>();
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
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