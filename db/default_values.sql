INSERT INTO categories(name) VALUES("unknown");
INSERT INTO CONSTANTS(name, value) VALUES("category_unknown", last_insert_rowid());

INSERT INTO categories(name) VALUES("noun_masculine");
INSERT INTO CONSTANTS(name, value) VALUES("category_noun_masculine", last_insert_rowid());

INSERT INTO categories(name) VALUES("noun_feminine");
INSERT INTO CONSTANTS(name, value) VALUES("category_noun_feminine", last_insert_rowid());

INSERT INTO categories(name) VALUES("noun_neutral");
INSERT INTO CONSTANTS(name, value) VALUES("category_noun_neutral", last_insert_rowid());

INSERT INTO categories(name) VALUES("noun_plural");
INSERT INTO CONSTANTS(name, value) VALUES("category_noun_plural", last_insert_rowid());

INSERT INTO categories(name) VALUES("pronoun");
INSERT INTO CONSTANTS(name, value) VALUES("category_pronoun", last_insert_rowid());

INSERT INTO categories(name) VALUES("verb");
INSERT INTO CONSTANTS(name, value) VALUES("category_verb", last_insert_rowid());

INSERT INTO categories(name) VALUES("adjective");
INSERT INTO CONSTANTS(name, value) VALUES("category_adjective", last_insert_rowid());

INSERT INTO categories(name) VALUES("adverb");
INSERT INTO CONSTANTS(name, value) VALUES("category_adverb", last_insert_rowid());

INSERT INTO categories(name) VALUES("conjunction");
INSERT INTO CONSTANTS(name, value) VALUES("category_conjunction", last_insert_rowid());

INSERT INTO categories(name) VALUES("preposition");
INSERT INTO CONSTANTS(name, value) VALUES("category_preposition", last_insert_rowid());

INSERT INTO categories(name) VALUES("interjection");
INSERT INTO CONSTANTS(name, value) VALUES("category_interjection", last_insert_rowid());

INSERT INTO categories(name) VALUES("sentence");
INSERT INTO CONSTANTS(name, value) VALUES("category_sentence", last_insert_rowid());

INSERT INTO categories(name) VALUES("abreviation");
INSERT INTO CONSTANTS(name, value) VALUES("category_abreviation", last_insert_rowid());
