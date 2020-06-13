pragma foreign_keys = on;

BEGIN TRANSACTION;

CREATE table version(major, minor, patch);
INSERT INTO version VALUES(0, 0, 1);



CREATE TABLE categories(
  id INTEGER PRIMARY KEY,
  name TEXT
);



CREATE TABLE languages(
  id INTEGER PRIMARY KEY,
  name TEXT
);



CREATE TABLE translations(
  id_word_src INTEGER NOT NULL,
  id_word_dst INTEGER,

  FOREIGN KEY(id_word_src) REFERENCES words(id)
  FOREIGN KEY(id_word_dst) REFERENCES words(id)
);



CREATE TABLE plurals(
  id_word INTEGER NOT NULL,
  name TEXT,

  FOREIGN KEY(id_word) REFERENCES words(id)
);



CREATE TABLE words(
  id INTEGER PRIMARY KEY,
  id_language INTEGER NOT NULL,
  id_category INTEGER NOT NULL,

  name TEXT,

  FOREIGN KEY(id_category) REFERENCES categories(id)
  FOREIGN KEY(id_language) REFERENCES languages(id)
);



.read default_values.sql

-- user specific values
.read custom/default_values.sql


COMMIT;
