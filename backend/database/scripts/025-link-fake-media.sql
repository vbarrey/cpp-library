INSERT INTO media_genres (media_id, genre_id) 
SELECT m.id, g.id 
FROM media m
CROSS JOIN genres g
WHERE random() < 0.15;