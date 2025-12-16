-- 4. Number of movies with a 10.0 rating
SELECT
    COUNT(*)
FROM
    movies
    JOIN ratings ON movies.id == ratings.movie_id
WHERE
    rating == 10.0;
