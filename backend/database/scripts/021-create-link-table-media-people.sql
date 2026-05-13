CREATE TABLE media_people (
    media_id UUID NOT NULL REFERENCES media(id) ON DELETE CASCADE,
    person_id UUID NOT NULL REFERENCES people(id) ON DELETE CASCADE,
    role TEXT NOT NULL,
    PRIMARY KEY(media_id, person_id, role)
);