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
    'MOVIE'::media_type,
    'Movie ' || i,
    'Description for movie ' || i,
    'https://picsum.photos/seed/movie' || i || '/300/450',
    CURRENT_DATE - ((i % 3650) * INTERVAL '1 day'),
    NOW(),
    NOW()
FROM generate_series(1, 150) AS s(i);
