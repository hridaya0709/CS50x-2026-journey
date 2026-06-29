-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0

SELECT people.name FROM movies, ratings, directors, people WHERE
movies.id = ratings.movie_id AND
movies.id = directors.movie_id AND
people.id = directors.person_id AND
ratings.rating >= 9.0;
