--Kevin Hance
--Due 10/8/2019
--CPSC 321
--DBMS HW4

-- Start by dropping all previous versions of our tables in an order
-- that doesn't cause foreign key constraint issues
DROP TABLE IF EXISTS music_influences;
DROP TABLE IF EXISTS album;
DROP TABLE IF EXISTS music_artist;
DROP TABLE IF EXISTS music_group;
DROP TABLE IF EXISTS record_label;
DROP TABLE IF EXISTS genre;
DROP TABLE IF EXISTS record_label_type;

-- create table to keep track of different types of record labels
CREATE TABLE record_label_type(
	label_type_id SMALLINT,
	label_type VARCHAR(100),
	PRIMARY KEY (label_type_id)
);
INSERT INTO record_label_type VALUES (0, "major");
INSERT INTO record_label_type VALUES (1, "indie");
INSERT INTO record_label_type VALUES (2, "hip-hop");

-- create table to keep track of separate record label companies
CREATE TABLE record_label(
	label_name VARCHAR(100),
	year_of_founding SMALLINT,
	label_type_id SMALLINT,
	FOREIGN KEY (label_type_id) REFERENCES record_label_type (label_type_id),
	PRIMARY KEY (label_name)
);

INSERT INTO record_label VALUES ("Famous Label", 2000, 0);
INSERT INTO record_label VALUES ("Underground Label", 2013, 1);
INSERT INTO record_label VALUES ("Real Ones Entertainment", 1987, 2);
INSERT INTO record_label VALUES ("Ref Jam Productions", 1987, 2);

-- create table to keep track of different genres of music
CREATE TABLE genre(
	genre VARCHAR(100),
	PRIMARY KEY (genre)
);

INSERT INTO genre VALUES ("rock");
INSERT INTO genre VALUES ("indie-rock");
INSERT INTO genre VALUES ("hip-hop");
INSERT INTO genre VALUES (" ");

-- create table to keep track of different music groups
CREATE TABLE music_group(
	group_name VARCHAR(100),
	year_of_founding YEAR,
	genre1 VARCHAR(30),
	genre2 VARCHAR(30),
	genre3 VARCHAR(30),
	FOREIGN KEY (genre1) REFERENCES genre (genre),
	FOREIGN KEY (genre2) REFERENCES genre (genre),
	FOREIGN KEY (genre3) REFERENCES genre (genre),
	PRIMARY KEY (group_name)
);

INSERT INTO music_group VALUES ("MusicMakers", 2005, "rock", " ", " ");
INSERT INTO music_group VALUES ("Beat Creators", 2008, "indie-rock", "rock","hip-hop");
INSERT INTO music_group VALUES ("The Rappers", 1998, "hip-hop", " ", " ");
INSERT INTO music_group VALUES ("A Tribe Called Question", 1981, "hip-hop", "rock", "indie-rock");
INSERT INTO music_group VALUES ("Jim Bean", 1981, "hip-hop", "rock", "indie-rock");
INSERT INTO music_group VALUES (" ", 0, " ", " ", " ");

-- create table to keep track of albums and their songs
CREATE TABLE album(
	title VARCHAR(100),
	music_group VARCHAR(100),
	year_of_recording SMALLINT,
	songs VARCHAR(1000),
	record_label VARCHAR(100),
	FOREIGN KEY (record_label) REFERENCES record_label (label_name),
	FOREIGN KEY (music_group) REFERENCES music_group (group_name),
	PRIMARY KEY (title, music_group)
);

INSERT INTO album VALUES ("Great Album", "MusicMakers", 2010, "song1, song2, song3, song4, song5", "Famous Label");
INSERT INTO album VALUES ("Unknown Album", "Beat Creators", 2009, "songA, songB, songC, songD, songE", "Underground Label");
INSERT INTO album VALUES ("Rap Album", "The Rappers", 1999, "beat1, beat2, beat3, beat4, beat5", "Real Ones Entertainment");
INSERT INTO album VALUES ("Another Rap Album", "A Tribe Called Question", 1999, "beat1, beat2, beat3, beat4, beat5", "Ref Jam Productions");
INSERT INTO album VALUES ("Jim's Album", "Jim Bean", 1991, "firstSong, secondSong, thirdSong", "Ref Jam Productions");
INSERT INTO album VALUES ("Jim's Second Album", "Jim Bean", 1993, "songOne, songTwo, songThree", "Ref Jam Productions");

-- create table to keep track of individual music artists
CREATE TABLE music_artist(
	first_name VARCHAR(50),
	last_name VARCHAR(50),
	birth_year SMALLINT,
	range_of_activity VARCHAR(30),
	music_group1 VARCHAR(100) NOT NULL,
	music_group2 VARCHAR(100),
	music_group3 VARCHAR(100),
	FOREIGN KEY (music_group1) REFERENCES music_group (group_name),
	FOREIGN KEY (music_group2) REFERENCES music_group (group_name),
	FOREIGN KEY (music_group3) REFERENCES music_group (group_name),
	PRIMARY KEY (first_name, last_name)
);

INSERT INTO music_artist VALUES ("John", "Doe", 1984, "2005-present", "MusicMakers", " ", " ");
INSERT INTO music_artist VALUES ("Jim", "Bean", 1974, "2009-present", "Beat Creators", " ", " ");
INSERT INTO music_artist VALUES ("Jack", "Peterson", 1970, "1998-present", "The Rappers", " ", " ");
INSERT INTO music_artist VALUES ("Josh", "Johnson", 1968, "1998-present", "The Rappers", "A Tribe Called Question", "MusicMakers");
INSERT INTO music_artist VALUES ("Joanna", "Jacobson", 1962, "1981-present", "A Tribe Called Question", "The Rappers", "Beat Creators");

-- create table to keep track of music influences (which groups influence other groups)
CREATE TABLE music_influences(
	music_group VARCHAR(100),
	is_influenced_by VARCHAR(100),
	PRIMARY KEY (music_group, is_influenced_by),
	FOREIGN KEY (is_influenced_by) REFERENCES music_group (group_name),
	FOREIGN KEY (music_group) REFERENCES music_group (group_name)
);

INSERT INTO music_influences VALUES ("A Tribe Called Question", "The Rappers");
INSERT INTO music_influences VALUES ("A Tribe Called Question", "MusicMakers");
INSERT INTO music_influences VALUES ("The Rappers", "A Tribe Called Question");
INSERT INTO music_influences VALUES ("Jim Bean", "A Tribe Called Question");

-- question 1
SELECT title FROM album WHERE year_of_recording = 1999;
-- question 2
SELECT label_name FROM record_label WHERE year_of_founding = 1987 AND label_type_id = 2;
-- question 3
SELECT label_name FROM record_label WHERE year_of_founding >= 1980 AND year_of_founding <= 1989 AND label_type_id = 2;
-- question 4
SELECT first_name, last_name FROM music_artist WHERE music_group1 = "The Rappers" OR music_group2 = "The Rappers" OR music_group3 = "The Rappers";
-- question 5
SELECT first_name, last_name FROM music_artist WHERE music_group2 != " ";
-- question 6
SELECT group_name, year_of_founding FROM music_group WHERE genre1 != " " AND genre2 != " " AND genre3 != " ";
-- question 7
SELECT music_group FROM music_influences WHERE is_influenced_by = "A Tribe Called Question";
-- question 8
SELECT DISTINCT title FROM album NATURAL JOIN music_artist WHERE music_group = CONCAT(first_name, " ", last_name) AND year_of_recording >= 1990 AND year_of_recording <= 1999;
-- question 9
SELECT DISTINCT first_name, last_name, group_name FROM music_group, music_artist WHERE genre2 != " ";
-- question 10
SELECT a.music_group, b.music_group, a.songs FROM album a, album b WHERE a.songs = b.songs AND a.music_group != b.music_group;
-- question 11
SELECT group_name, year_of_founding FROM music_group NATURAL JOIN music_influences WHERE is_influenced_by = "A Tribe Called Question" AND year_of_founding < 2000 AND year_of_founding > 1900;
