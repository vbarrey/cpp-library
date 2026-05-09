CREATE TABLE series (
    media_id UUID PRIMARY KEY REFERENCES media(id) ON DELETE CASCADE,
    seasons INT
);