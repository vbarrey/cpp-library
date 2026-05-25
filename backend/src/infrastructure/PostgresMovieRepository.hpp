#pragma once

#include "../application/IMovieRepository.hpp"
#include "../domain/Result.hpp"
#include "../domain/media/MediaType.hpp"
#include "../domain/media/Genre.hpp"

#include "../domain/media/dto/CreateMovieDTO.hpp"
#include "../domain/media/dto/ImportMovieDTO.hpp"

#include <pqxx/pqxx>

class PostgresMovieRepository : public IMovieRepository {
public:
    explicit PostgresMovieRepository(const std::string& connStr)
        : connection(connStr) {
    }

    Result<std::vector<Movie>> findAll() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec(R"(
                SELECT
                    me.id,
                    me.type,
                    me.title,
                    me.description,
                    me.cover_url,
                    me.rating,
                    me.release_date,
                    me.created_at,
                    me.updated_at,
                    
                    COALESCE(
                        json_agg(
                            json_build_object(
                                'id', g.id,
                                'name', g.name
                            )
                        ) FILTER (WHERE g.id IS NOT NULL),
                        '[]'
                    ) as genres,

                    mo.director,
                    mo.duration_minutes
                FROM media me
                JOIN movies mo ON mo.media_id = me.id
                LEFT JOIN media_genres mg ON mg.media_id = me.id
                LEFT JOIN genres g ON mg.genre_id = g.id
                GROUP BY me.id, mo.media_id
                ORDER BY me.created_at DESC, me.id DESC
            )");

            std::vector<Movie> movies;

            for (const auto& row : result) {
                movies.push_back(mapMovieRow(row));
            }

            return movies;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Movie>> findPaginated(int limit, int offset) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                SELECT
                    me.id,
                    me.type,
                    me.title,
                    me.description,
                    me.cover_url,
                    me.rating,
                    me.release_date,
                    me.created_at,
                    me.updated_at,
                    
                     COALESCE(
                        json_agg(
                            json_build_object(
                                'id', g.id,
                                'name', g.name
                            )
                        ) FILTER (WHERE g.id IS NOT NULL),
                        '[]'
                    ) as genres,

                    mo.director,
                    mo.duration_minutes
                FROM media me
                JOIN movies mo ON mo.media_id = me.id
                LEFT JOIN media_genres mg ON mg.media_id = me.id
                LEFT JOIN genres g ON mg.genre_id = g.id
                GROUP BY me.id, mo.media_id
                ORDER BY me.created_at DESC, me.id DESC
                LIMIT $1 
                OFFSET $2)",
                limit,
                offset
            );

            std::vector<Movie> movies;
            for (const auto& row : result) {
                movies.push_back(mapMovieRow(row));
            }

            return movies;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<int> count() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec("SELECT COUNT(mo.media_id) FROM movies mo INNER JOIN media me ON me.id = mo.media_id");

            return result[0][0].as<int>();
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<Movie> create(const CreateMovieDTO& movie) override {
        try {
            pqxx::work txn(connection);

            auto mediaResult = txn.exec_params(R"(
                INSERT INTO media (
                    id,
                    type,
                    title,
                    description,
                    cover_url,
                    rating
                )
                VALUES (
                    gen_random_uuid(),
                    'MOVIE',
                    $1,
                    $2,
                    $3,
                    $4
                )
                RETURNING id)",
                movie.media.title,
                movie.media.description,
                movie.media.coverUrl,
                movie.media.rating
            );

            std::string mediaId = mediaResult[0]["id"].as<std::string>();

            txn.exec_params(R"(
                INSERT INTO movies (
                    media_id,
                    director,
                    duration_minutes
                )
                VALUES ($1, $2, $3))",
                mediaId,
                movie.director,
                movie.durationMinutes
            );

            txn.commit();

            return movie.toDomain(mediaId);
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<Movie> externalImport(const ImportMovieDTO& movieImport) override {
        try {
            pqxx::work txn(connection);

            auto existsResult = txn.exec_params(R"(SELECT id FROM external_ids WHERE external_id = $1 AND source = $2)", movieImport.externalId, externalSourceToString(movieImport.source));

            if (!existsResult.empty()) { return std::unexpected( DomainError{ "Movie import already exists in database"}); }

            auto mediaResult = txn.exec_params(R"(
                INSERT INTO media (
                    id,
                    type,
                    title,
                    description,
                    cover_url,
                    rating
                )
                VALUES (
                    gen_random_uuid(),
                    'MOVIE',
                    $1,
                    $2,
                    $3,
                    $4
                )
                RETURNING id)",
                movieImport.movie.media.title,
                movieImport.movie.media.description,
                movieImport.movie.media.coverUrl,
                movieImport.movie.media.rating
            );

            std::string mediaId = mediaResult[0]["id"].as<std::string>();

            txn.exec_params(R"(
                INSERT INTO movies (
                    media_id,
                    director,
                    duration_minutes
                )
                VALUES ($1, $2, $3))",
                mediaId,
                movieImport.movie.director,
                movieImport.movie.durationMinutes
            );

            txn.exec_params(R"(
                INSERT INTO external_ids (
                    id,
                    media_id,
                    external_id,
                    source
                ) 
                SELECT
                    gen_random_uuid(),
                    $1,
                    $2,
                    $3)",
                mediaId,
                movieImport.externalId,
                externalSourceToString(movieImport.source)
            );

            txn.commit();

            return movieImport.toDomain(mediaId);
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

private:
    pqxx::connection connection;

    Movie mapMovieRow(pqxx::row_ref movie_row) {
        return Movie{
            Media{
                movie_row["id"].as<std::string>(),
                MediaType::MOVIE,
                movie_row["title"].as<std::string>(),
                movie_row["description"].as<std::string>(""),
                movie_row["cover_url"].as<std::string>(""),
                Genre::mapGenreRow(movie_row),
                movie_row["release_date"].as<std::string>(""),
                movie_row["created_at"].as<std::string>(""),
                movie_row["updated_at"].as<std::string>(""),
                movie_row["rating"].as<double>(-1)
            },
            movie_row["director"].as<std::string>(""),
            movie_row["duration_minutes"].as<int>(0)
        };
    };
};