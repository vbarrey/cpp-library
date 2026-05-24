CREATE TABLE media (
    id UUID PRIMARY KEY,
    type media_type NOT NULL,
    title TEXT NOT NULL,
    description TEXT,
    cover_url TEXT,
    rating DOUBLE PRECISION,
    release_date DATE,
    created_at TIMESTAMP NOT NULL DEFAULT NOW(),
    updated_at TIMESTAMP NOT NULL DEFAULT NOW()
);