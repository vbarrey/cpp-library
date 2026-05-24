#pragma once

#include "../../integrations/tmdb/clients/TMDbClient.hpp"
#include "../../infrastructure/PostgresMovieRepository.hpp"
#include "../../domain/ExternalSource.hpp"
#include "../../domain/media/MediaType.hpp"

#include <iostream>

inline void importMovie(Config config, int startPage, int maxPages) {

    std::cout << "START ACTION 'import-movies'" << std::endl;

    TMDbClient client(config.tmdb.api_key);

    std::string connStr = config.getPostgresConnexionStr();

    auto movieRepo = std::make_unique<PostgresMovieRepository>(connStr);

    int total = 0;
    int inserted = 0;

    for (int index = startPage; index < startPage + maxPages; index++) {

        auto response = client.discoverMovies(index);

        std::cout
            << "Page: "
            << response.page
            << std::endl;

        for (const auto& movie : response.results) {
            auto result = movieRepo->externalImport({
                {
                    {
                        MediaType::MOVIE,
                        movie.title,
                        movie.overview,
                        movie.poster_path.has_value() ? "https://image.tmdb.org/t/p/w500/" + movie.poster_path.value() : "",
                        {},
                        movie.release_date,
                        movie.vote_average
                    },
                    "", // TO UPDATE with director
                    0 // TO UPDATE with durationMinutes
                },
                ExternalSource::TMDb,
                std::to_string(movie.id)
                });

            if (result.has_value()) inserted++;
            else std::cout << result.error().description << std::endl ;
        }

        total += response.results.size();
    }
    std::cout << "ACTION RESULT FOR 'import-movies' : " + std::to_string(inserted) + " movies inserted into database over the " + std::to_string(total) + " imported from TMDb" << std::endl;
}