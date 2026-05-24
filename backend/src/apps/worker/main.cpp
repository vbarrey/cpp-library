#include "../../config/ConfigLoader.hpp"

#include "../../integrations/tmdb/applications/TMDbImportService.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2) {

        std::cerr
            << "Missing action"
            << std::endl;

        return 1;
    }

    std::string action = argv[1];

    const Config config = ConfigLoader::load("config.json");

    if (action == "import-movies") {

        int startPage = 1;
        int maxPages = 1;

        if (argc >= 3) {
            startPage = std::stoi(argv[2]);
        }

        if (argc >= 4) {
            maxPages = std::stoi(argv[3]);
        }

        importMovie(config, startPage, maxPages);

    }
    else {

        std::cerr
            << "Unknown action"
            << std::endl;

        return 1;
    }

    return 0;
}