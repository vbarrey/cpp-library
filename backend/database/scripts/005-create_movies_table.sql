CREATE TABLE movies (
    media_id UUID PRIMARY KEY REFERENCES media(id) ON DELETE CASCADE,
    director TEXT,
    duration_minutes INTEGER
);