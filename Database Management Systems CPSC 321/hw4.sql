--Kevin Hance
--DBMS HW4

DROP TABLE IF EXISTS album;
DROP TABLE IF EXISTS music_artist;
DROP TABLE IF EXISTS music_group;
DROP TABLE IF EXISTS record_label;
DROP TABLE IF EXISTS genre;
DROP TABLE IF EXISTS record_label_type;

CREATE TABLE record_label_type(
	label_type_id SMALLINT,
	label_type VARCHAR(100),
	PRIMARY KEY (label_type_id)
);
INSERT INTO record_label_type VALUES (0, "major");
INSERT INTO record_label_type VALUES (1, "indie");
INSERT INTO record_label_type VALUES (2, "hip-hop");

CREATE TABLE record_label(
	label_name VARCHAR(100),
	year_of_founding SMALLINT,
	label_type_id SMALLINT,
	FOREIGN KEY (label_type_id) REFERENCES record_label_type (label_type_id),
	PRIMARY KEY (label_name)
);

INSERT INTO record_label VALUES ("Famous Label", 2000, 0);
INSERT INTO record_label VALUES ("Underground Label", 2013, 1);
INSERT INTO record_label VALUES ("Real Ones Entertainment", 1997, 2);

CREATE TABLE genre(
	genre VARCHAR(100),
	PRIMARY KEY (genre)
);

INSERT INTO genre VALUES ("rock");
INSERT INTO genre VALUES ("indie-rock");
INSERT INTO genre VALUES ("hip-hop");

CREATE TABLE music_group(
	group_name VARCHAR(100),
	year_of_founding YEAR,
	genre VARCHAR(30),
	FOREIGN KEY (genre) REFERENCES genre (genre),
	PRIMARY KEY (group_name)
);

INSERT INTO music_group VALUES ("MusicMakers", 2005, "rock");
INSERT INTO music_group VALUES ("Beat Creators", 2008, "indie-rock");
INSERT INTO music_group VALUES ("The Rappers", 1998, "hip-hop");

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

CREATE TABLE music_artist(
	first_name VARCHAR(50),
	last_name VARCHAR(50),
	birth_year SMALLINT,
	range_of_activity VARCHAR(30),
	music_group VARCHAR(100),
	FOREIGN KEY (music_group) REFERENCES music_group (group_name),
	PRIMARY KEY (first_name, last_name)
);

INSERT INTO music_artist VALUES ("John", "Doe", 1984, "2005-present", "MusicMakers");
INSERT INTO music_artist VALUES ("Jim", "Bean", 1974, "2009-present", "Beat Creators");
INSERT INTO music_artist VALUES ("Jack", "Peterson", 1970, "1999-present", "The Rappers");





