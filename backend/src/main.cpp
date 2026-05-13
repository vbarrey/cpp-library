#include <crow.h>
#include "presentation/BookController.hpp"
#include "presentation/MovieController.hpp"
#include "presentation/GameController.hpp"
#include "presentation/AuthController.hpp"

#include "infrastructure/PostgresBookRepository.hpp"
#include "infrastructure/PostgresMovieRepository.hpp"
#include "infrastructure/PostgresGameRepository.hpp"
#include "infrastructure/PostgresUserRepository.hpp"

#include "application/BookService.hpp"
#include "application/MovieService.hpp"
#include "application/GameService.hpp"
#include "application/AuthService.hpp"

#include "config/ConfigLoader.hpp"
#include "config/CorsMiddleware.hpp"

int main() {
    crow::App<CorsMiddleware> app;

    auto config = ConfigLoader::load("config.json");

    std::string connStr =
        "dbname=" + config.database.name +
        " user=" + config.database.user +
        " password=" + config.database.password +
        " host=" + config.database.host +
        " port=" + std::to_string(config.database.port);

    auto bookRepo = std::make_unique<PostgresBookRepository>(connStr);
    auto bookService = std::make_unique<BookService>(std::move(bookRepo));

    auto movieRepo = std::make_unique<PostgresMovieRepository>(connStr);
    auto movieService = std::make_unique<MovieService>(std::move(movieRepo));
    
    auto gameRepo = std::make_unique<PostgresGameRepository>(connStr);
    auto gameService = std::make_unique<GameService>(std::move(gameRepo));

    auto userRepo = std::make_unique<PostgresUserRepository>(connStr);
    auto authService = std::make_unique<AuthService>(std::move(userRepo));

    AuthController authController(std::move(authService));
    authController.registerRoutes(app);

    BookController bookController(std::move(bookService));
    bookController.registerRoutes(app);

    MovieController movieController(std::move(movieService));
    movieController.registerRoutes(app);

    GameController gameController(std::move(gameService));
    gameController.registerRoutes(app);

    app.port(18080).multithreaded().run();
}