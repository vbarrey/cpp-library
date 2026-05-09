CREATE TABLE books (
    media_id UUID PRIMARY KEY REFERENCES media(id) ON DELETE CASCADE,
    author TEXT,
    isbn TEXT,
    page_count INT,
    publisher TEXT
);