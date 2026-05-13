CREATE TABLE media_genres (
    media_id UUID NOT NULL REFERENCES media(id) ON DELETE CASCADE,
    genre_id UUID NOT NULL REFERENCES genres(id) ON DELETE CASCADE,
    PRIMARY KEY(media_id, genre_id)
);