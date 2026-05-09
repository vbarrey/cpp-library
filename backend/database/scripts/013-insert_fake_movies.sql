INSERT INTO movies (
    media_id,
    director,
    duration_minutes,
    genre,
    rating
)
SELECT
    m.id,
    CASE
        WHEN row_number() OVER () % 4 = 0 THEN 'Director Alpha'
        WHEN row_number() OVER () % 4 = 1 THEN 'Director Beta'
        WHEN row_number() OVER () % 4 = 2 THEN 'Director Gamma'
        ELSE 'Director Delta'
    END,
    90 + ((row_number() OVER () * 13) % 150),
    CASE
        WHEN row_number() OVER () % 5 = 0 THEN 'Action'
        WHEN row_number() OVER () % 5 = 1 THEN 'Comedy'
        WHEN row_number() OVER () % 5 = 2 THEN 'Drama'
        WHEN row_number() OVER () % 5 = 3 THEN 'Horror'
        ELSE 'Sci-Fi'
    END,
    (row_number() OVER () % 50) / 10.0 + 5.0
FROM media m
WHERE m.type = 'MOVIE';
