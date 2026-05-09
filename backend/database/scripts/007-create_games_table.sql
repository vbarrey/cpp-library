CREATE TABLE games (
    media_id UUID PRIMARY KEY REFERENCES media(id) ON DELETE CASCADE,
    platform TEXT
);