-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
SELECT
    DISTINCT name
FROM
    people
    JOIN directors ON directors.person_id = people.id
    JOIN movies ON movies.id = directors.movie_id
    JOIN ratings ON ratings.movie_id = movies.id
WHERE
    rating >= 9.0;
