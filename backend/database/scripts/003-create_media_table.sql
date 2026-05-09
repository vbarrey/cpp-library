CREATE TABLE media (
    id UUID PRIMARY KEY,
    type media_type NOT NULL,
    title TEXT NOT NULL,
    description TEXT,
    cover_url TEXT,
    release_date DATE,
    created_at TIMESTAMP NOT NULL DEFAULT NOW(),
    updated_at TIMESTAMP NOT NULL DEFAULT NOW()
);