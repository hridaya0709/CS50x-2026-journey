-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred

SELECT DISTINCT movies.title FROM movies, stars, people WHERE
    stars.person_id = people.id AND
    stars.movie_id = movies.id AND
    people.name IN ('Jennifer Lawrence', 'Bradley Cooper')
    GROUP BY movies.id HAVING COUNT(*) = 2;

-- SELECT movies.title FROM movies, stars WHERE
-- stars.movie_id = movies.id AND
-- movies.id IN (
--     SELECT movies.id FROM movies, stars, people WHERE
--     stars.person_id = people.id AND
--     stars.movie_id = movies.id AND
--     people.name IN ('Jennifer Lawrence', 'Bradley Cooper')
--     GROUP BY movies.id HAVING COUNT(*) = 2
-- );



-- SELECT movies.title FROM
-- movies JOIN stars ON stars.movie_id = movies.id
-- people JOIN stars ON stars.person_id = people.id
-- WHERE movies.id IN (
--     SELECT stars.movie_id FROM stars WHERE stars.person_id IN (
--         SELECT id FROM people WHERE name IN ('Jennifer Lawrence', 'Bradley Cooper')
--     ));

-- SELECT movies.title FROM movies, people, stars WHERE
-- stars.movie_id = movies.id AND
-- stars.person_id = people.id AND
-- stars.person_id in (SELECT people.id FROM people WHERE name IN ('Jennifer Lawrence', 'Bradley Cooper'));

-- SELECT movies.title FROM movies, people, stars WHERE
-- stars.movie_id = movies.id AND
-- stars.person_id = people.id AND
-- people.name IN ('Jennifer Lawrence', 'Bradley Cooper');
