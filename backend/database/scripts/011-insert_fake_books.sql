INSERT INTO books (
    media_id,
    author,
    isbn,
    page_count,
    publisher
)
SELECT
    m.id,
    CASE
        WHEN row_number() OVER () % 3 = 0 THEN 'Author A'
        WHEN row_number() OVER () % 3 = 1 THEN 'Author B'
        ELSE 'Author C'
    END,
    '978-' || LPAD((100000000 + row_number() OVER ())::TEXT, 9, '0'),
    100 + ((row_number() OVER () * 7) % 500),
    CASE
        WHEN row_number() OVER () % 3 = 0 THEN 'Publisher Alpha'
        WHEN row_number() OVER () % 3 = 1 THEN 'Publisher Beta'
        ELSE 'Publisher Gamma'
    END
FROM media m
WHERE m.type = 'BOOK';