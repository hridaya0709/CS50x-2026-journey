-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred

SELECT name FROM stars, people, movies WHERE
stars.person_id = people.id AND
stars.movie_id = movies.id AND
people.name != 'Kevin Bacon' AND
movies.id in (
    SELECT movies.id FROM movies, stars, people WHERE
    stars.person_id = people.id AND
    stars.movie_id = movies.id AND
    people.name = 'Kevin Bacon' and people.birth = '1958'
);
