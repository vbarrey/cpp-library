struct CorsMiddleware {
    struct context {};

    void before_handle(
        crow::request&,
        crow::response&,
        context&
    ) {
    }

    void after_handle(
        crow::request&,
        crow::response& res,
        context&
    ) {
        res.set_header(
            "Access-Control-Allow-Origin",
            "http://localhost:3000"
        );

        res.set_header(
            "Access-Control-Allow-Methods",
            "GET, POST, OPTIONS"
        );

        res.set_header(
            "Access-Control-Allow-Headers",
            "Content-Type"
        );
    }
};