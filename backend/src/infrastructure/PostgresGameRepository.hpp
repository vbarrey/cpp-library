#pragma once

#include "../application/IGameRepository.hpp"
#include "../domain/Result.hpp"
#include "../domain/media/MediaType.hpp"
#include "../domain/media/Genre.hpp"
#include <pqxx/pqxx>

class PostgresGameRepository : public IGameRepository {
public:
    explicit PostgresGameRepository(const std::string& connStr)
        : connection(connStr) {
    }

    Result<std::vector<Game>> findAll() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec(R"(
                SELECT
                    m.id,
                    m.type,
                    m.title,
                    m.description,
                    m.cover_url,
                    
                    COALESCE(
                        json_agg(
                            json_build_object(
                                'id', ge.id,
                                'name', ge.name
                            )
                        ) FILTER (WHERE ge.id IS NOT NULL),
                        '[]'
                    ) as genres,

                    m.rating,
                    g.developer,
                    g.platform,
                    g.multiplayer
                FROM media m
                JOIN games g ON g.media_id = m.id
                LEFT JOIN media_genres mg ON mg.media_id = m.id
                LEFT JOIN genres ge ON mg.genre_id = ge.id
                GROUP BY m.id, g.media_id
                ORDER BY m.created_at DESC, m.id DESC
            )");

            std::vector<Game> games;

            for (const auto& row : result) {
                games.push_back(mapGameRow(row));
            }

            return games;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<std::vector<Game>> findPaginated(int limit, int offset) override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec_params(R"(
                SELECT
                    m.id,
                    m.type,
                    m.title,
                    m.description,
                    m.cover_url,
                    
                    COALESCE(
                        json_agg(
                            json_build_object(
                                'id', ge.id,
                                'name', ge.name
                            )
                        ) FILTER (WHERE ge.id IS NOT NULL),
                        '[]'
                    ) as genres,

                    m.rating,
                    g.developer,
                    g.platform,
                    g.multiplayer
                FROM media m
                JOIN games g ON g.media_id = m.id
                LEFT JOIN media_genres mg ON mg.media_id = m.id
                LEFT JOIN genres ge ON mg.genre_id = ge.id
                GROUP BY m.id, g.media_id
                ORDER BY m.created_at DESC, m.id DESC
                LIMIT $1 
                OFFSET $2)",
                limit,
                offset
            );

            std::vector<Game> games;
            for (const auto& row : result) {
                games.push_back(mapGameRow(row));
            }

            return games;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<int> count() override {
        try {
            pqxx::work txn(connection);

            auto result = txn.exec("SELECT COUNT(g.media_id) FROM games g INNER JOIN media m ON m.id = g.media_id");

            return result[0][0].as<int>();
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

    Result<Game> create(const Game& game) override {
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
                    'GAME',
                    $1,
                    $2,
                    $3,
                    $4
                )
                RETURNING id)",
                game.media.title,
                game.media.description,
                game.media.coverUrl,
                game.media.rating
            );

            std::string mediaId = mediaResult[0]["id"].as<std::string>();

            txn.exec_params(R"(
                INSERT INTO games (
                    media_id,
                    developer,
                    platform,
                    multiplayer
                )
                VALUES ($1, $2, $3, $4))",
                mediaId,
                game.developer,
                game.platform,
                game.multiplayer
            );

            txn.commit();

            Game createdGame = game;
            createdGame.media.id = mediaId;
            createdGame.media.type = MediaType::GAME;

            return createdGame;
        }
        catch (const std::exception& e) {
            return std::unexpected(DomainError{ e.what() });
        }
    }

private:
    pqxx::connection connection;

    Game mapGameRow(pqxx::row_ref game_row) {
        return Game{
            Media{
                game_row["id"].as<std::string>(),
                MediaType::GAME,
                game_row["title"].as<std::string>(),
                game_row["description"].as<std::string>(""),
                game_row["cover_url"].as<std::string>(""),
                Genre::mapGenreRow(game_row),
                game_row["rating"].as<double>(-1)
            }, 
            game_row["developer"].as<std::string>(""),
            game_row["platform"].as<std::string>(""),
            game_row["multiplayer"].as<bool>(false)
        };
    };
};