-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated

SELECT movies.title FROM movies, stars, people, ratings WHERE
stars.movie_id = movies.id AND
stars.person_id = people.id AND
ratings.movie_id = movies.id AND
people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;
