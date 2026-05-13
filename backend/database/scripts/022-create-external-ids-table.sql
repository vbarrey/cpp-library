CREATE TABLE external_ids (
    id UUID PRIMARY KEY,
    media_id UUID NOT NULL REFERENCES media(id) ON DELETE CASCADE,
    source TEXT NOT NULL,
    external_id TEXT NOT NULL,
    UNIQUE(source, external_id)
);