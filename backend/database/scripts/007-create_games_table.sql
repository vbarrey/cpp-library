CREATE TABLE games (
    media_id UUID PRIMARY KEY REFERENCES media(id) ON DELETE CASCADE,
    developer TEXT,
    platform TEXT,
    multiplayer BOOLEAN
);