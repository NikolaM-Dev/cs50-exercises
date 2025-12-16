-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT
    title
FROM
    movies
WHERE
    id IN (
        SELECT
            movies.id
        FROM
            movies
            JOIN stars ON stars.movie_id = movies.id
            JOIN people ON people.id = stars.person_id
        WHERE
            name = 'Jennifer Lawrence'
    )
    AND id IN (
        SELECT
            movies.id
        FROM
            movies
            JOIN stars ON stars.movie_id = movies.id
            JOIN people ON people.id = stars.person_id
        WHERE
            name = 'Bradley Cooper'
    );
