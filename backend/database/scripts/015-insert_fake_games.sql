INSERT INTO games (
    media_id,
    developer,
    platform,
    genre,
    multiplayer
)
SELECT
    m.id,
    CASE
        WHEN row_number() OVER () % 4 = 0 THEN 'Studio Alpha'
        WHEN row_number() OVER () % 4 = 1 THEN 'Studio Beta'
        WHEN row_number() OVER () % 4 = 2 THEN 'Studio Gamma'
        ELSE 'Studio Delta'
    END,
    CASE
        WHEN row_number() OVER () % 3 = 0 THEN 'PC'
        WHEN row_number() OVER () % 3 = 1 THEN 'PlayStation'
        ELSE 'Xbox'
    END,
    CASE
        WHEN row_number() OVER () % 5 = 0 THEN 'RPG'
        WHEN row_number() OVER () % 5 = 1 THEN 'FPS'
        WHEN row_number() OVER () % 5 = 2 THEN 'Strategy'
        WHEN row_number() OVER () % 5 = 3 THEN 'Sports'
        ELSE 'Adventure'
    END,
    (row_number() OVER () % 2) = 0
FROM media m
WHERE m.type = 'GAME';
