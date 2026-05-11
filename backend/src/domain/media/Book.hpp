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

struct PaginatedBooks {
    std::vector<Book> data;
    int total;
    int page;
    int limit;
};

inline void to_json(nlohmann::json& j, const Book& b) {
    j = nlohmann::json{
        {"id", b.media.id},
        {"title", b.media.title},
        {"author", b.author},
        {"isbn", b.isbn},
        {"pageCount", b.pageCount},
        {"publisher", b.publisher},
        {"coverUrl", b.media.coverUrl},
        {"description", b.media.description}
    };
}

inline void from_json(const nlohmann::json& j, Book& b) {
    j.at("id").get_to(b.media.id);
    j.at("title").get_to(b.media.title);
    j.at("author").get_to(b.author);
    j.at("isbn").get_to(b.isbn);
    j.at("pageCount").get_to(b.pageCount);
    j.at("publisher").get_to(b.publisher);
}