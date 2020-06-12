pragma foreign_keys = on;

BEGIN TRANSACTION;

CREATE table version(major, minor, patch);
INSERT INTO version VALUES(0, 0, 1);


CREATE TABLE categories(
  id INTEGER PRIMARY KEY,
  name TEXT
);

INSERT INTO categories(name) VALUES("unknown");
INSERT INTO categories(name) VALUES("noun_masculine");
INSERT INTO categories(name) VALUES("noun_feminine");
INSERT INTO categories(name) VALUES("noun_neutral");
INSERT INTO categories(name) VALUES("noun_plural");
INSERT INTO categories(name) VALUES("pronoun");
INSERT INTO categories(name) VALUES("verb");
INSERT INTO categories(name) VALUES("adjective");
INSERT INTO categories(name) VALUES("adverb");
INSERT INTO categories(name) VALUES("conjunction");
INSERT INTO categories(name) VALUES("preposition");
INSERT INTO categories(name) VALUES("interjection");
INSERT INTO categories(name) VALUES("sentence");
INSERT INTO categories(name) VALUES("abreviation");



CREATE TABLE languages(
  id INTEGER PRIMARY KEY,
  name TEXT
);


CREATE table words(
  id INTEGER PRIMARY KEY,
  id_category INTEGER NOT NULL,
  FOREIGN KEY(id_category) REFERENCES categories(id)
);



.read default_values.sql

END TRANSACTION;
