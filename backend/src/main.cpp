#include <crow.h>
#include "presentation/BookController.hpp"
#include "infrastructure/PostgresBookRepository.hpp"
#include "application/BookService.hpp"
#include "config/ConfigLoader.hpp"

int main() {
    crow::SimpleApp app;

    auto config = ConfigLoader::load();

    std::string connStr =
        "dbname=" + config.database.name +
        " user=" + config.database.user +
        " password=" + config.database.password +
        " host=" + config.database.host +
        " port=" + std::to_string(config.database.port);

    auto repo = std::make_unique<PostgresBookRepository>(connStr);
    auto service = std::make_unique<BookService>(std::move(repo));

    BookController controller(std::move(service));
    controller.registerRoutes(app);

    app.port(18080).multithreaded().run();
}