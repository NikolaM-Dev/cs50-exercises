-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT
    DISTINCT name
FROM
    people
    JOIN stars ON stars.person_id = people.id
WHERE
    stars.movie_id IN (
        SELECT
            movies.id
        FROM
            movies
            JOIN stars ON stars.movie_id = movies.id
            JOIN people ON people.id = stars.person_id
        WHERE
            name = 'Kevin Bacon'
            AND birth = 1958
    )
    AND people.id NOT IN (
        SELECT
            id
        FROM
            people
        WHERE
            name = 'Kevin Bacon'
            AND birth = 1958
    )
