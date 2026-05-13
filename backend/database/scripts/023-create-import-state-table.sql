CREATE TABLE import_state (
    id UUID PRIMARY KEY,
    provider TEXT NOT NULL,
    import_type TEXT NOT NULL,
    current_page INTEGER NOT NULL DEFAULT 1,
    total_pages INTEGER,
    status TEXT NOT NULL,
    updated_at TIMESTAMP NOT NULL DEFAULT NOW()
);