#include "TMDbMovieMapper.hpp"

Movie TMDbMovieMapper::toDomain(const TMDbMovieDTO& dto)
{
    return Movie{
        Media{
            "",
            MediaType::MOVIE,
            dto.title,
            dto.overview,
            dto.posterPath.value_or(""),
            {},
            static_cast<int>(dto.voteAverage)
        },
        ""
        0
    };
}