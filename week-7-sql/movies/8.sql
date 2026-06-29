-- 8. Names of people who starred in Toy Story

SELECT people.name FROM people, movies, stars WHERE
stars.movie_id = movies.id AND
stars.person_id = people.id AND
movies.title = 'Toy Story';
