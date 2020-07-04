#include <iostream>
#include <stdexcept>

#include <gtkmm.h>

extern "C" {
#include <lib/sqlite3.h>
}

#include <DB.hh>
#include <db_tables.hh>



// Static members definition
sqlite3* DB::_db;



void DB::initialize(const std::string file_name)
{
  if (sqlite3_open(file_name.c_str(), &_db))
  {
    std::cerr << "Failure opening DB:\n\t" << sqlite3_errmsg(_db) << '\n';
    throw "Failure opening DB";
  }
  std::cout << "DB OPENED\n";
}



std::vector<std::string> DB::getTableEntries(const std::string &table)
{
  std::vector<std::string> results;
  std::string request = "SELECT * FROM " + table;

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(_db, request.c_str(), -1, &stmt, NULL) != SQLITE_OK)
  {
    std::cerr << "[DB] Failure preparing request [" << request << "]\n\t"
              << sqlite3_errmsg(_db) << '\n';
    sqlite3_close(_db);
    throw std::runtime_error("[DB] Failure executing [" + request + "]:\n");
  }

  while (sqlite3_step(stmt) == SQLITE_ROW)
  {
    results.push_back((char*) sqlite3_column_text(stmt, 1));
  }

  if (sqlite3_finalize(stmt) != SQLITE_OK)
  {
    std::cerr << "[DB] Failure finalizing request [" << request << "]\n\t"
              << sqlite3_errmsg(_db) << '\n';
    sqlite3_close(_db);
    throw std::runtime_error("[DB] Failure executing [" + request + "]:\n");
  }

  return results;
}



bool DB::addWord(const std::string& name, int language, int category)
{
  std::cout << "adding word" << std::endl;
  std::string request = "INSERT INTO words(id_language, id_category, name) VALUES("
    + std::to_string(language) + ", "
    + std::to_string(category) + ", "
    + "'" + name + "');"; /// \todo Handle escape quoting

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(_db, request.c_str(), -1, &stmt, NULL) != SQLITE_OK)
  {
    std::cerr << "[DB] Failure preparing request [" << request << "]\n\t"
              << sqlite3_errmsg(_db) << '\n';
    sqlite3_close(_db);
    return false;
  }

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    std::cerr << "[DB] Failure step; request [" << request << "]\n\t"
              << sqlite3_errmsg(_db) << '\n';
    sqlite3_close(_db);
    return false;
  }

  if (sqlite3_finalize(stmt) != SQLITE_OK)
  {
    std::cerr << "[DB] Failure finalizing request [" << request << "]\n\t"
              << sqlite3_errmsg(_db) << '\n';
    sqlite3_close(_db);
    return false;
  }

  return true;
}



void DB::getWordsLanguageSorted(int language_id, void *first)
{
  const std::string request =
    "SELECT * FROM words WHERE id_language=" + std::to_string(language_id) + " ORDER BY name ASC";
  rawRequest(request.c_str(), dbFetchWords, first);
}



void DB::getWord(int word_id, void *first)
{
  const std::string request = "SELECT * FROM words WHERE id=" + std::to_string(word_id);
  rawRequest(request.c_str(), dbFetchWords, first);
}



void DB::getTranslations(int word_src_id,
                         int (*cb) (void*, int, char**, char**),
                         void *first)
{
  auto request {"SELECT * FROM translations WHERE id_word_src = "
                + std::to_string(word_src_id)};
  rawRequest(request.c_str(), cb, first);
}



void DB::getGrammarRulesTitles(void *first)
{
  const std::string request =
    "SELECT * FROM grammar_rules ORDER BY title ASC";
  rawRequest(request.c_str(), fetchGrammarRulesTitles, first);
}



void DB::getGrammarExamples(int grammar_rule_id, void *first)
{
  const std::string request =
    "SELECT name FROM words WHERE id in (SELECT id_word FROM grammar_examples WHERE id_rule="
    + std::to_string(grammar_rule_id) + ")";

  rawRequest(request.c_str(), fetchGrammarExamples, first);
}



void DB::rawRequest(const std::string request,
                    int (*cb) (void*, int, char**, char**),
                    void *first)
{
  char *err_msg = 0;
  if (sqlite3_exec(_db, request.c_str(), cb, first, &err_msg) != SQLITE_OK)
  {
    std::cerr << "[DB] Error executing [" << request << "]:\n\t" << err_msg << '\n';
    sqlite3_free(err_msg);
    sqlite3_close(_db);
    throw std::runtime_error("[DB] Failure executing [" + request + "]:\n");
  }
}



void DB::close()
{
  sqlite3_close(_db);
}



int DB::dbFetchWords(void *model, int argc, char **argv, char **azColName)
{
  Gtk::ListStore *treeModel = (Gtk::ListStore *) model;
  Gtk::TreeModel::Row row = *(treeModel->append());
  DbTableColumnsWords tableCol;
  row[tableCol.id] = std::stoi(argv[0]);
  row[tableCol.language] = std::stoi(argv[1]);
  row[tableCol.category] = std::stoi(argv[2]);
  row[tableCol.name] = argv[3];

  return 0;
}



int DB::fetchTranslations(void *model, int argc, char **argv, char **azColName)
{
  Gtk::ListStore *treeModel = (Gtk::ListStore *) model;
  Gtk::TreeModel::Row row = *(treeModel->append());
  DbTableColumnsTranslations tableCol;
  row[tableCol.id_word_src] = std::stoi(argv[0]);
  row[tableCol.id_word_dst] = std::stoi(argv[1]);

  return 0;
}



int DB::fetchGrammarRulesTitles(void *model, int argc, char** argv, char **azColName)
{
  Gtk::ListStore *treeModel = (Gtk::ListStore *) model;
  Gtk::TreeModel::Row row = *(treeModel->append());
  DbTableGrammarRules tableCol;
  row[tableCol.id] = std::stoi(argv[0]);
  row[tableCol.title] = argv[1];
  row[tableCol.content] = argv[2];

  return 0;
}



int DB::fetchGrammarExamples(void *model, int argc, char** argv, char **azColName)
{
  Gtk::ListStore *treeModel = (Gtk::ListStore *) model;
  Gtk::TreeModel::Row row = *(treeModel->append());
  DbViewGrammarExampleNames names;
  row[names.name] = argv[0];

  return 0;
}
