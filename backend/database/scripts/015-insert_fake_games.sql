INSERT INTO games (
    media_id,
    developer,
    platform,
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
    (row_number() OVER () % 2) = 0
FROM media m
WHERE m.type = 'GAME';
