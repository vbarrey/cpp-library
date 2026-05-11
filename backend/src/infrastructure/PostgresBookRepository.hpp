#pragma once

#include "../application/IBookRepository.hpp"
#include "../domain/Result.hpp"
#include <pqxx/pqxx>
#include "../domain/media/MediaType.hpp"

class PostgresBookRepository : public IBookRepository {
public:
    explicit PostgresBookRepository(const std::string& connStr)
        : connection(connStr) {
    }

    Result<std::vector<Book>> findAll() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec(R"(
                SELECT
                    m.id,
                    m.type,
                    m.title,
                    m.description,
                    m.cover_url,
                    b.author,
                    b.isbn,
                    b.page_count,
                    b.publisher
                FROM media m
                JOIN books b ON b.media_id = m.id
                ORDER BY m.created_at DESC
            )");

            std::vector<Book> books;

            for (const auto& row : result) {
                books.push_back(mapBookRow(row));
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

            auto result = txn.exec_params(R"(
                SELECT
                    m.id,
                    m.type,
                    m.title,
                    m.description,
                    m.cover_url,
                    b.author,
                    b.isbn,
                    b.page_count,
                    b.publisher
                FROM media m
                JOIN books b ON b.media_id = m.id
                ORDER BY m.created_at DESC, m.id DESC
                LIMIT $1 
                OFFSET $2)",
                limit,
                offset
            );

            std::vector<Book> books;
            for (const auto& row : result) {
                books.push_back(mapBookRow(row));
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

            auto result = txn.exec("SELECT COUNT(b.media_id) FROM books b INNER JOIN media m ON m.id = b.media_id");

            return result[0][0].as<int>();
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<Book> create(const Book& book) override {
        try {
            pqxx::work txn(connection);

            auto mediaResult = txn.exec_params(R"(
                INSERT INTO media (
                    id,
                    type,
                    title,
                    description,
                    cover_url
                )
                VALUES (
                    gen_random_uuid(),
                    'BOOK',
                    $1,
                    $2,
                    $3
                )
                RETURNING id)",
                book.media.title,
                book.media.description,
                book.media.coverUrl
            );

            std::string mediaId = mediaResult[0]["id"].as<std::string>();

            txn.exec_params(R"(
                INSERT INTO books (
                    media_id,
                    author,
                    isbn,
                    page_count,
                    publisher
                )
                VALUES ($1, $2, $3, $4, $5))",
                mediaId,
                book.author,
                book.isbn,
                book.pageCount,
                book.publisher
            );

            txn.commit();

            Book createdBook = book;
            createdBook.media.id = mediaId;
            createdBook.media.type = MediaType::BOOK;

            return createdBook;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

private:
    pqxx::connection connection;

    Book mapBookRow(pqxx::row_ref book_row) {
        return Book{
                Media{
                    book_row["id"].as<std::string>(),
                    MediaType::BOOK,
                    book_row["title"].as<std::string>(),
                    book_row["description"].as<std::string>(""),
                    book_row["cover_url"].as<std::string>("")
                },
                book_row["author"].as<std::string>(""),
                book_row["isbn"].as<std::string>(""),
                book_row["page_count"].as<int>(0),
                book_row["publisher"].as<std::string>("")
        };
    };
};