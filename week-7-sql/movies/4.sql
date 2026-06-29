-- 4. Number of movies with a 10.0 rating

SELECT COUNT(id) FROM movies, ratings WHERE
movies.id = ratings.movie_id AND rating = 10.0;
