#include <string>
#include "MediaType.hpp"

struct Media {
    std::string id;
    MediaType type;
    std::string title;
    std::string description;
    std::string coverUrl;
};