INSERT INTO series (
    media_id,
    director,
    seasons
)
SELECT
    id,
    CASE
        WHEN row_number() OVER () % 4 = 0 THEN 'Director Alpha'
        WHEN row_number() OVER () % 4 = 1 THEN 'Director Beta'
        WHEN row_number() OVER () % 4 = 2 THEN 'Director Gamma'
        ELSE 'Director Delta'
    END,
    1 + (row_number() OVER () % 5)
FROM media
WHERE type = 'SERIES'
LIMIT 100;