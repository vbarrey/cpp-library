INSERT INTO media (
    id,
    type,
    title,
    description,
    cover_url,
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
    CURRENT_DATE - ((i % 3650) * INTERVAL '1 day'),
    NOW(),
    NOW()
FROM generate_series(1, 200) AS s(i);