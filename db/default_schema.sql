pragma foreign_keys = on;

BEGIN TRANSACTION;

CREATE table version(major, minor, patch);
INSERT INTO version VALUES(0, 0, 1);


CREATE TABLE categories(
  id INTEGER PRIMARY KEY,
  name TEXT
);

INSERT INTO categories(id, name) VALUES(1,  "unknown");
INSERT INTO categories(id, name) VALUES(2,  "noun_masculine");
INSERT INTO categories(id, name) VALUES(3,  "noun_feminine");
INSERT INTO categories(id, name) VALUES(4,  "noun_neutral");
INSERT INTO categories(id, name) VALUES(5,  "noun_plural");
INSERT INTO categories(id, name) VALUES(6,  "pronoun");
INSERT INTO categories(id, name) VALUES(7,  "verb");
INSERT INTO categories(id, name) VALUES(8,  "adjective");
INSERT INTO categories(id, name) VALUES(9,  "adverb");
INSERT INTO categories(id, name) VALUES(10, "conjunction");
INSERT INTO categories(id, name) VALUES(11, "preposition");
INSERT INTO categories(id, name) VALUES(12, "interjection");
INSERT INTO categories(id, name) VALUES(13, "sentence");
INSERT INTO categories(id, name) VALUES(14, "abreviation");



CREATE TABLE languages(
  id INTEGER PRIMARY KEY,
  name TEXT
);


CREATE table words(
  id INTEGER PRIMARY KEY,
  id_language INTEGER NOT NULL,
  id_category INTEGER NOT NULL,

  name TEXT,

  FOREIGN KEY(id_category) REFERENCES categories(id)
  FOREIGN KEY(id_language) REFERENCES languages(id)
);



.read default_values.sql

COMMIT;
