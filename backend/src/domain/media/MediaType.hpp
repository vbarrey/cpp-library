#pragma once

#include <optional>

enum class MediaType
{
    BOOK,
    MOVIE,
    SERIES,
    GAME
};

inline std::optional<MediaType> mediaTypeFromString(const std::string& value)
{
    if (value == "BOOK") {
        return MediaType::BOOK;
    }

    if (value == "MOVIE") {
        return MediaType::MOVIE;
    }

    if (value == "SERIES") {
        return MediaType::SERIES;
    }

    if (value == "GAME") {
        return MediaType::GAME;
    }

    return std::nullopt;
}

inline std::string mediaTypeToString(const MediaType& mediaType)
{
    switch (mediaType) {
    case MediaType::BOOK:
        return "BOOK";
    case MediaType::GAME:
        return "GAME";
    case MediaType::MOVIE:
        return "MOVIE";
    case MediaType::SERIES:
        return "SERIES";
    default:
        return "";
    }
}