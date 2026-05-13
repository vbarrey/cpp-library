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
    'SERIES'::media_type,
    'Series ' || i,
    'Description for series ' || i,
    'https://picsum.photos/seed/series' || i || '/300/450',
    CASE
        WHEN row_number() OVER () % 5 = 0 THEN 'Drama'
        WHEN row_number() OVER () % 5 = 1 THEN 'Comedy'
        WHEN row_number() OVER () % 5 = 2 THEN 'Action'
        WHEN row_number() OVER () % 5 = 3 THEN 'Horror'
        ELSE 'Romance'
    END,
    (row_number() OVER () % 50) / 10.0 + 5.0,
    CURRENT_DATE - ((i % 3650) * INTERVAL '1 day'),
    NOW(),
    NOW()
FROM generate_series(1, 100) AS s(i);