#include <crow.h>
#include "presentation/BookController.hpp"
#include "presentation/AuthController.hpp"
#include "infrastructure/PostgresBookRepository.hpp"
#include "infrastructure/PostgresUserRepository.hpp"
#include "application/BookService.hpp"
#include "application/AuthService.hpp"
#include "config/ConfigLoader.hpp"

int main() {
    crow::SimpleApp app;

    auto config = ConfigLoader::load("config.json");

    std::string connStr =
        "dbname=" + config.database.name +
        " user=" + config.database.user +
        " password=" + config.database.password +
        " host=" + config.database.host +
        " port=" + std::to_string(config.database.port);

    auto bookRepo = std::make_unique<PostgresBookRepository>(connStr);
    auto bookService = std::make_unique<BookService>(std::move(bookRepo));

    auto userRepo = std::make_unique<PostgresUserRepository>(connStr);
    auto authService = std::make_unique<AuthService>(std::move(userRepo));

    AuthController authController(std::move(authService));
    authController.registerRoutes(app);

    BookController controller(std::move(bookService));
    controller.registerRoutes(app);

    app.port(18080).multithreaded().run();
}