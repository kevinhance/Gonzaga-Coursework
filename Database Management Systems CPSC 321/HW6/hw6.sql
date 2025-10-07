-- Kevin Hance
-- DBMS (CPSC 321)
-- HW6 (hw6.sql)

DROP TABLE IF EXISTS border;
DROP TABLE IF EXISTS city;
DROP TABLE IF EXISTS province;
DROP TABLE IF EXISTS country;

CREATE TABLE country(
    country_code VARCHAR(10),
    country_name VARCHAR(50),
    gdp INT UNSIGNED,
    inflation FLOAT,
    PRIMARY KEY (country_code)
);

CREATE TABLE province(
    province_name VARCHAR(50),
    country_code VARCHAR(10),
    area FLOAT UNSIGNED,
    PRIMARY KEY (province_name, country_code),
    FOREIGN KEY (country_code) REFERENCES country (country_code)
);

CREATE TABLE city(
    city_name VARCHAR(50),
    province_name VARCHAR(50),
    country_code VARCHAR(10),
    population INT UNSIGNED,
    PRIMARY KEY (city_name, province_name, country_code),
    FOREIGN KEY (province_name, country_code) REFERENCES province (province_name, country_code)
);

CREATE TABLE border(
    country_code_1 VARCHAR(10),
    country_code_2 VARCHAR(10),
    border_length FLOAT UNSIGNED,
    PRIMARY KEY (country_code_1, country_code_2),
    FOREIGN KEY (country_code_1) REFERENCES country (country_code),
    FOREIGN KEY (country_code_2) REFERENCES country (country_code)
);

INSERT INTO country VALUES ('OS', 'Oswaldo', 78000, 6.7);
INSERT INTO country VALUES ('RL', 'Renlandia', 54000, 1.7);
INSERT INTO country VALUES ('GN', 'Geneva', 65000, 2.1);

INSERT INTO province VALUES ('Oslodo', 'OS', 8712);
INSERT INTO province VALUES ('St. Janice', 'OS', 76650);

INSERT INTO province VALUES ('Huport', 'RL', 91030);
INSERT INTO province VALUES ('Flaubury', 'RL', 5690);

INSERT INTO province VALUES ('Antalens', 'GN', 72003);
INSERT INTO province VALUES ('Huport', 'GN', 54041);

INSERT INTO city VALUES ('Tesa', 'Oslodo', 'OS', 964);
INSERT INTO city VALUES ('Sluurgan', 'Oslodo', 'OS', 5919);
INSERT INTO city VALUES ('Belogonia', 'St. Janice', 'OS', 97635);
INSERT INTO city VALUES ('Britano', 'St. Janice', 'OS', 33434);

INSERT INTO city VALUES ('Piolas', 'Huport', 'RL', 46626);
INSERT INTO city VALUES ('Stombus', 'Huport', 'RL', 49384);
INSERT INTO city VALUES ('Outling', 'Flaubury', 'RL', 127);
INSERT INTO city VALUES ('Whita', 'Flaubury', 'RL', 52743);

INSERT INTO city VALUES ('Blumore', 'Antalens', 'GN', 54000);
INSERT INTO city VALUES ('Juefbert', 'Antalens', 'GN', 120);
INSERT INTO city VALUES ('Tesa', 'Huport', 'GN', 11043);
INSERT INTO city VALUES ('Stombus', 'Huport', 'GN', 13299);

INSERT INTO border VALUES ('OS', 'GN', 4800);
INSERT INTO border VALUES ('GN', 'RL', 4500);
INSERT INTO border VALUES ('RL', 'OS', 1200);
INSERT INTO border VALUES ('GN', 'OS', 4800);
INSERT INTO border VALUES ('RL', 'GN', 4500);
INSERT INTO border VALUES ('OS', 'GN', 1200);


-- group concat question
SELECT * FROM city;
SELECT GROUP_CONCAT(city_name) FROM city WHERE population > 1000;

-- stddev pop question
SELECT * FROM city;
SELECT STDDEV_POP(population), AVG(population) FROM city WHERE population > 2000;

-- union vs union all question
SELECT * FROM city;
(SELECT * FROM city WHERE population > 1000)
UNION
(SELECT * FROM city WHERE population < 20000);

(SELECT * FROM city WHERE population > 1000)
UNION ALL
(SELECT * FROM city WHERE population < 20000);

-- TECHNICAL WORK

-- question 1
-- all create/insert statements

-- question 2
SET @gdp = 60000;
SET @inflation = 3.0;
SET @area = 10000;

SELECT DISTINCT c.country_name, c.country_code, c.gdp, c.inflation
FROM province p, country c
WHERE c.country_code = p.country_code
AND  c.gdp > @gdp
AND  c.inflation > @inflation
AND  p.area < @area;

-- question 3
SELECT DISTINCT c.country_name, c.country_code, c.gdp, c.inflation
FROM province p INNER JOIN country c ON c.country_code = p.country_code
WHERE c.gdp > @gdp
AND  c.inflation > @inflation
AND  p.area < @area;

--question 4
SET @population = 1000;

SELECT p.country_code, c.country_name, p.province_name, ct.city_name, ct.population, p.area
FROM country c, province p, city ct
WHERE p.country_code = c.country_code
AND p.province_name = ct.province_name
AND ct.population < @population;

--question 5

SELECT p.country_code, c.country_name, p.province_name, ct.city_name, ct.population, p.area
FROM country c
INNER JOIN province p ON p.country_code = c.country_code
INNER JOIN city ct ON p.province_name = ct.province_name
WHERE ct.population < @population;

-- question 6
SELECT SUM(area) FROM province;

-- question 7
SELECT MIN(gdp), MAX(gdp), AVG(gdp), MIN(inflation), MAX(inflation), AVG(inflation)
FROM country;

-- question 8
SET @country_code = 'OS';
SELECT COUNT(*), AVG(population) FROM city WHERE country_code = @country_code;

-- question 9
SET @province_name = "Oslodo";
SELECT AVG(population) FROM city WHERE province_name = @province_name;
