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
    'GAME'::media_type,
    'Game ' || i,
    'Description for game ' || i,
    'https://picsum.photos/seed/game' || i || '/300/450',
    CASE
        WHEN row_number() OVER () % 5 = 0 THEN 'Action'
        WHEN row_number() OVER () % 5 = 1 THEN 'Adventure'
        WHEN row_number() OVER () % 5 = 2 THEN 'RPG'
        WHEN row_number() OVER () % 5 = 3 THEN 'Strategy'
        ELSE 'Sports'
    END,
    (row_number() OVER () % 50) / 10.0 + 5.0,
    CURRENT_DATE - ((i % 3650) * INTERVAL '1 day'),
    NOW(),
    NOW()
FROM generate_series(1, 100) AS s(i);
