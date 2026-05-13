INSERT INTO media (
    id,
    type,
    title,
    description,
    cover_url,
    genre,
    rating,
    release_date,
    created_at,
    updated_at
)
SELECT
    gen_random_uuid(),
    'BOOK'::media_type,
    'Book ' || i,
    'Description for book ' || i,
    'https://picsum.photos/seed/book' || i || '/300/450',
    CASE
        WHEN row_number() OVER () % 5 = 0 THEN 'Fiction'
        WHEN row_number() OVER () % 5 = 1 THEN 'Non-Fiction'
        WHEN row_number() OVER () % 5 = 2 THEN 'Science Fiction'
        WHEN row_number() OVER () % 5 = 3 THEN 'Fantasy'
        ELSE 'Mystery'
    END,
    (row_number() OVER () % 50) / 10.0 + 5.0,
    CURRENT_DATE - ((i % 3650) * INTERVAL '1 day'),
    NOW(),
    NOW()
FROM generate_series(1, 200) AS s(i);