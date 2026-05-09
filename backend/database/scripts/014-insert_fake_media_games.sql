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
    'GAME'::media_type,
    'Game ' || i,
    'Description for game ' || i,
    'https://picsum.photos/seed/game' || i || '/300/450',
    CURRENT_DATE - ((i % 3650) * INTERVAL '1 day'),
    NOW(),
    NOW()
FROM generate_series(1, 100) AS s(i);
