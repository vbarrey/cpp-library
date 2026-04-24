#pragma once
#include <string>
#include <nlohmann/json.hpp>

struct Book {
    int id;
    std::string title;
    std::string author;
};

struct PaginatedBooks {
    std::vector<Book> data;
    int total;
    int page;
    int limit;
};

inline void to_json(nlohmann::json& j, const Book& b) {
    j = nlohmann::json{
        {"id", b.id},
        {"title", b.title},
        {"author", b.author}
    };
}

inline void from_json(const nlohmann::json& j, Book& b) {
    j.at("id").get_to(b.id);
    j.at("title").get_to(b.title);
    j.at("author").get_to(b.author);
}