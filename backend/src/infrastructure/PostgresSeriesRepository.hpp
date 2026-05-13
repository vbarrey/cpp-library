#pragma once

#include "../application/ISeriesRepository.hpp"
#include "../domain/Result.hpp"
#include "../domain/media/MediaType.hpp"
#include <pqxx/pqxx>

class PostgresSeriesRepository : public ISeriesRepository {
public:
    explicit PostgresSeriesRepository(const std::string& connStr)
        : connection(connStr) {
    }

    Result<std::vector<Series>> findAll() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec(R"(
                SELECT
                    m.id,
                    m.type,
                    m.title,
                    m.description,
                    m.cover_url,
                    m.genre,
                    m.rating,
                    s.director,
                    s.seasons
                FROM media m
                JOIN series s ON s.media_id = m.id
                ORDER BY m.created_at DESC, m.id DESC
            )");

            std::vector<Series> series;

            for (const auto& row : result) {
                series.push_back(mapSeriesRow(row));
            }

            return series;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Series>> findPaginated(int limit, int offset) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                SELECT
                    m.id,
                    m.type,
                    m.title,
                    m.description,
                    m.cover_url,
                    m.genre,
                    m.rating,
                    s.director,
                    s.seasons
                FROM media m
                JOIN series s ON s.media_id = m.id
                ORDER BY m.created_at DESC, m.id DESC
                LIMIT $1 
                OFFSET $2)",
                limit,
                offset
            );

            std::vector<Series> series;
            for (const auto& row : result) {
                series.push_back(mapSeriesRow(row));
            }

            return series;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<int> count() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec("SELECT COUNT(s.media_id) FROM series s INNER JOIN media m ON m.id = s.media_id");

            return result[0][0].as<int>();
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<Series> create(const Series& series) override {
        try {
            pqxx::work txn(connection);

            auto mediaResult = txn.exec_params(R"(
                INSERT INTO media (
                    id,
                    type,
                    title,
                    description,
                    cover_url,
                    genre,
                    rating
                )
                VALUES (
                    gen_random_uuid(),
                    'SERIES',
                    $1,
                    $2,
                    $3,
                    $4,
                    $5
                )
                RETURNING id)",
                series.media.title,
                series.media.description,
                series.media.coverUrl,
                series.media.genre,
                series.media.rating
            );

            std::string mediaId = mediaResult[0]["id"].as<std::string>();

            txn.exec_params(R"(
                INSERT INTO seriess (
                    media_id,
                    director,
                    seasons
                )
                VALUES ($1, $2, $3))",
                mediaId,
                series.director,
                series.seasons
            );

            txn.commit();

            Series createdSeries = series;
            createdSeries.media.id = mediaId;
            createdSeries.media.type = MediaType::SERIES;

            return createdSeries;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

private:
    pqxx::connection connection;

    Series mapSeriesRow(pqxx::row_ref series_row) {
        return Series{
            Media{
                series_row["id"].as<std::string>(),
                MediaType::SERIES,
                series_row["title"].as<std::string>(),
                series_row["description"].as<std::string>(""),
                series_row["cover_url"].as<std::string>(""),
                series_row["genre"].as<std::string>(""),
                series_row["rating"].as<int>(-1)
            },
            series_row["director"].as<std::string>(""),
            series_row["seasons"].as<int>(0)
        };
    };
};