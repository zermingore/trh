#ifndef DB_TABLES_HH_
# define DB_TABLES_HH_

#include <gtkmm.h>



class DbTableColumnsWords: public Gtk::TreeModel::ColumnRecord
{
public:
  DbTableColumnsWords() {
    add(id);
    add(language);
    add(category);
    add(name);
  }

  Gtk::TreeModelColumn<unsigned int> id;
  Gtk::TreeModelColumn<short> language;
  Gtk::TreeModelColumn<short> category;
  Gtk::TreeModelColumn<Glib::ustring> name;
};



class DbTableColumnsTranslations: public Gtk::TreeModel::ColumnRecord
{
public:
  DbTableColumnsTranslations() {
    add(id_word_src);
    add(id_word_dst);
  }

  Gtk::TreeModelColumn<unsigned int> id_word_src;
  Gtk::TreeModelColumn<unsigned int> id_word_dst;
};



class DbTableGrammarRules: public Gtk::TreeModel::ColumnRecord
{
public:
  DbTableGrammarRules() {
    add(id);
    add(title);
    add(content);
  }

  Gtk::TreeModelColumn<unsigned int> id;
  Gtk::TreeModelColumn<Glib::ustring> title;
  Gtk::TreeModelColumn<Glib::ustring> content;
};



class DbTableGrammarExamples: public Gtk::TreeModel::ColumnRecord
{
public:
  DbTableGrammarExamples() {
    add(id_rule);
    add(id_word);
  }

  Gtk::TreeModelColumn<unsigned int> id_rule;
  Gtk::TreeModelColumn<unsigned int> id_word;
};



class DbViewGrammarExampleNames: public Gtk::TreeModel::ColumnRecord
{
public:
  DbViewGrammarExampleNames() {
    add(name);
  }

  Gtk::TreeModelColumn<Glib::ustring> name;
};


#endif /* !DB_TABLES_HH_ */
