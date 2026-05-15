#pragma once

#include "../application/IGenreRepository.hpp"
#include "../domain/Result.hpp"
#include "../domain/media/MediaType.hpp"
#include <pqxx/pqxx>

class PostgresGenreRepository : public IGenreRepository {
public:
    explicit PostgresGenreRepository(const std::string& connStr)
        : connection(connStr) {
    }

    Result<std::vector<Genre>> findAll() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec(R"(
                SELECT
                    g.id,
                    g.name,
                FROM genres g
                ORDER BY g.name DESC
            )");

            std::vector<Genre> genres;

            for (const auto& row : result) {
                genres.push_back(mapGenreRow(row));
            }

            return genres;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Genre>> findPaginated(int limit, int offset) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                SELECT
                    g.id,
                    g.name
                FROM genres g
                ORDER BY g.name DESC
                LIMIT $1 
                OFFSET $2)",
                limit,
                offset
            );

            std::vector<Genre> genres;

            for (const auto& row : result) {
                genres.push_back(mapGenreRow(row));
            }

            return genres;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<int> count() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec("SELECT COUNT(g.id) FROM genres g");

            return result[0][0].as<int>();
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Genre>> findAllByMediaType(MediaType type) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                SELECT
                    g.id,
                    g.name,
                    COUNT(m.id)
                FROM genres g
                INNER JOIN media_genres md ON g.id = md.genre_id
                INNER JOIN media m ON md.media_id = m.id
                WHERE m.type = $1
                GROUP BY g.id
                ORDER BY g.name DESC)", 
                mediaTypeToString(type)
            );

            std::vector<Genre> genres;

            for (const auto& row : result) {
                genres.push_back(mapGenreRow(row));
            }

            return genres;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Genre>> findPaginatedByMediaType(MediaType type, int limit, int offset) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                SELECT
                    g.id,
                    g.name,
                    COUNT(m.id)
                FROM genres g
                INNER JOIN media_genres md ON g.id = md.genre_id
                INNER JOIN media m ON md.media_id = m.id
                WHERE m.type = $1
                GROUP BY g.id
                ORDER BY g.name DESC
                LIMIT $2
                OFFSET $3)",
                mediaTypeToString(type),
                limit,
                offset
            );

            std::vector<Genre> genres;

            for (const auto& row : result) {
                genres.push_back(mapGenreRow(row));
            }

            return genres;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<Genre> create(const Genre& genre) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                INSERT INTO genre (
                    id,
                    name
                )
                VALUES (
                    gen_random_uuid(),
                    $1
                )
                RETURNING id)",
                genre.name
            );

            std::string genreId = result[0]["id"].as<std::string>();

            Genre createdGenre = genre;
            createdGenre.id = genreId;

            return createdGenre;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    

private:
    pqxx::connection connection;

    Genre mapGenreRow(pqxx::row_ref genre_row) {
        return Genre{
            genre_row["id"].as<std::string>(""),
            genre_row["name"].as<std::string>("")
        };
    };
};