INSERT INTO books (title, author)
SELECT
    'Book ' || i,
    CASE
        WHEN i % 3 = 0 THEN 'Author A'
        WHEN i % 3 = 1 THEN 'Author B'
        ELSE 'Author C'
    END
FROM generate_series(1, 200) AS s(i);