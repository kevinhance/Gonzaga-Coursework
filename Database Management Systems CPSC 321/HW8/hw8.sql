-- Kevin Hance
-- HW8

-- READING ASSIGNMENT

-- Reading assignment question 2
WITH t AS (SELECT * FROM actor a WHERE a.actor_id > 20)
    SELECT * FROM t ORDER BY t.first_name DESC;

-- Reading assignment question 3
DROP TABLE IF EXISTS table_name;

CREATE TABLE table_name(
    column1 INT,
    column2 INT,
    column3 INT,
    PRIMARY KEY (column1)
);

INSERT INTO table_name VALUES (1, 2, 3);
INSERT INTO table_name VALUES (4, 5, 6);
INSERT INTO table_name VALUES (7, 8, 9);

UPDATE table_name
SET
    column2 = 6,
    column3 = 10
WHERE
    column3 = 6;

SELECT * FROM table_name;

UPDATE table_name
SET
    column2 = 10,
    column3 = 15
WHERE
    column3 > 5;

SELECT * FROM table_name;

DELETE FROM table_name WHERE column1 = 1;

SELECT * FROM table_name;

DELETE FROM table_name WHERE column2 > 0;

SELECT * FROM table_name;

-- Reading assignment question 4

DROP TABLE IF EXISTS people;
DROP TABLE IF EXISTS people_location;

CREATE TABLE people(
    user_identification INT UNSIGNED,
    first_name VARCHAR(30),
    last_name VARCHAR(30),
    age INT UNSIGNED,
    PRIMARY KEY (user_identification)
);

INSERT INTO people VALUES (0, "Kevin", "Hance", 21);
INSERT INTO people VALUES (1, "Jane", "Hance", 59);
INSERT INTO people VALUES (2, "Barry", "Hance", 58);

CREATE TABLE people_location(
    user_identification INT UNSIGNED,
    location_city VARCHAR(30),
    PRIMARY KEY (user_identification)
);

INSERT INTO people_location VALUES (0, "Spokane");
INSERT INTO people_location VALUES (1, "Woodinville");
INSERT INTO people_location VALUES (2, "Woodinville");

SELECT * FROM people;
SELECT * FROM people_location;

SELECT *
FROM people RIGHT JOIN people_location
ON people.user_identification = people_location.user_identification;

-- TECHINICAL WORK

-- Question 1
SELECT a.first_name, a.last_name, count(f.film_id)
FROM actor a JOIN film f JOIN film_actor fa
ON a.actor_id = fa.actor_id AND f.film_id = fa.film_id
GROUP BY a.actor_id
ORDER BY count(f.film_id) DESC;

-- Question 2
SELECT c.name, count(fc.film_id)
FROM category c JOIN film_category fc
ON c.category_id = fc.category_id
GROUP BY fc.category_id
ORDER BY count(fc.film_id) DESC;

-- Question 3
SELECT c.first_name, c.last_name, count(r.rental_id) AS pg_films_at_299
FROM customer c JOIN rental r ON c.customer_id = r.customer_id
JOIN inventory i ON r.inventory_id = i.inventory_id
JOIN payment p ON p.rental_id = r.rental_id
JOIN film f ON i.film_id = f.film_id
WHERE f.rating = "PG" AND p.amount = 2.99
GROUP BY c.customer_id
HAVING count(r.rental_id) >= 4
ORDER BY count(r.rental_id) DESC;

-- Question 4
SELECT f.title, max(p.amount) AS max_rental_payment_for_movie
FROM rental r JOIN inventory i ON r.inventory_id = i.inventory_id
JOIN film f ON f.film_id = i.film_id
JOIN payment p ON p.rental_id = r.rental_id
WHERE f.rating = "G" AND p.amount = (   SELECT max(p.amount)
                                        FROM rental r JOIN inventory i ON r.inventory_id = i.inventory_id
                                        JOIN film f ON f.film_id = i.film_id
                                        JOIN payment p ON p.rental_id = r.rental_id 
                                        )
GROUP BY f.film_id;

-- Question 5
SELECT c.name, count(f.film_id)
FROM category c JOIN film_category fc ON c.category_id = fc.category_id
JOIN film f ON fc.film_id = f.film_id
WHERE f.rating = "PG"
GROUP BY c.category_id
HAVING count(f.film_id) = (SELECT max(val) AS max_films FROM 
                            (   SELECT count(f.film_id) AS val
                                FROM category c JOIN film_category fc ON c.category_id = fc.category_id
                                JOIN film f ON fc.film_id = f.film_id
                                WHERE f.rating = "PG"
                                GROUP BY c.category_id)
                            maximum)
ORDER BY count(f.film_id) DESC;

-- Question 6
SELECT f.title, count(r.rental_id)
FROM film f JOIN inventory i ON i.film_id = f.film_id
JOIN rental r ON r.inventory_id = i.inventory_id
WHERE f.rating = "G"
GROUP BY f.film_id
HAVING count(r.rental_id) > (   SELECT avg(val) AS max_times_rented
                                FROM (  SELECT count(r.rental_id) AS val
                                        FROM film f JOIN inventory i ON i.film_id = f.film_id
                                        JOIN rental r ON r.inventory_id = i.inventory_id
                                        WHERE f.rating = "G"
                                        GROUP BY f.film_id)
                             t)
ORDER BY count(r.rental_id) DESC;

-- Question 7
SELECT DISTINCT a1.first_name, a1.last_name
FROM film f JOIN film_actor fa ON f.film_id = fa.film_id
JOIN actor a1 ON a1.actor_id = fa.actor_id
WHERE NOT EXISTS (  SELECT a2.actor_id
                    FROM film f JOIN film_actor fa ON f.film_id = fa.film_id
                    JOIN actor a2 ON fa.actor_id = a2.actor_id
                    WHERE f.rating = "G" AND a1.actor_id = a2.actor_id);

-- Question 8
-- was unsure how to do this one

-- Question 9
SELECT DISTINCT a.actor_id, a.first_name, a.last_name, (SELECT count(g_films)
                                                        FROM (SELECT count(fa1.film_id) AS g_films
                    FROM film f1 JOIN film_actor fa1 ON f1.film_id = fa1.film_id
                    JOIN actor a1 ON a1.actor_id = fa1.actor_id
                    WHERE f1.rating = "G"
                    GROUP BY a1.actor_id) g_films_count)/(SELECT count(all_films)
                                                        FROM (SELECT count(fa2.film_id) AS all_films
                    FROM film f2 JOIN film_actor fa2 ON f2.film_id = fa2.film_id
                    JOIN actor a2 ON a2.actor_id = fa2.actor_id
                    GROUP BY a2.actor_id) all_films_count) AS percentage_g_movies
FROM film f JOIN film_actor fa ON f.film_id = fa.film_id
JOIN actor a ON a.actor_id = fa.actor_id
GROUP BY a.actor_id;

-- Question 10
SELECT f.title
FROM film f LEFT JOIN film_actor fa ON f.film_id = fa.film_id
WHERE fa.actor_id IS NULL;

-- Question 11
SELECT f.title
FROM film f JOIN inventory i ON f.film_id = i.film_id
LEFT JOIN rental r ON i.inventory_id = r.inventory_id
WHERE r.rental_id IS NULL;

-- Question 12
SELECT film_id, count(*)
FROM (
        SELECT DISTINCT f.film_id, a.actor_id
        FROM film f JOIN film_actor fa ON f.film_id = fa.film_id
        LEFT JOIN actor a ON a.actor_id = fa.actor_id) faq
GROUP BY faq.film_id
ORDER BY count(*);