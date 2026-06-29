-- 6. Average rating of movies in 2012

SELECT avg(rating) FROM movies, ratings WHERE
movies.id = ratings.movie_id AND movies.year = '2012';
