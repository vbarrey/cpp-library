#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "Media.hpp"

struct Book {
    Media media;
    std::string author;
    std::string isbn;
    int pageCount;
    std::string publisher;
};

inline void to_json(nlohmann::json& j, const Book& b) {
    j = nlohmann::json{
        {"id", b.media.id},
        {"title", b.media.title},
        {"coverUrl", b.media.coverUrl},
        {"description", b.media.description},
        {"genre", b.media.genre},
        {"rating", b.media.rating},
        {"type", "BOOK"},
        {"author", b.author},
        {"isbn", b.isbn},
        {"page_count", b.pageCount},
        {"publisher", b.publisher}
    };
}

inline void from_json(const nlohmann::json& j, Book& b) {
    j.at("id").get_to(b.media.id);
    j.at("title").get_to(b.media.title);
    j.at("coverUrl").get_to(b.media.coverUrl);
    j.at("description").get_to(b.media.description);
    j.at("genre").get_to(b.media.genre);
    j.at("rating").get_to(b.media.rating);
    j.at("type").get_to(b.media.type);
    j.at("author").get_to(b.author);
    j.at("isbn").get_to(b.isbn);
    j.at("page_count").get_to(b.pageCount);
    j.at("publisher").get_to(b.publisher);
}