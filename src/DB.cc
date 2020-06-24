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
    "SELECT * FROM grammar_examples";
  rawRequest(request.c_str(), fetchGrammarRulesTitles, first);


  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(_db, request.c_str(), -1, &stmt, NULL) != SQLITE_OK)
  {
    std::cerr << "[DB] Failure preparing [" << request << "]:\n\t"
              << sqlite3_errmsg(_db) << '\n';
    sqlite3_close(_db);
    throw std::runtime_error("[DB] Failure executing [" + request + "]:\n");
  }

  int rc = SQLITE_OK;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    std::cout << "stmt: word: " << sqlite3_column_text(stmt, 3) << std::endl;
  }
  if (rc != SQLITE_DONE) {
    std::cerr << "Failure stepping through [" << request << "]:\n\t"
              << sqlite3_errmsg(_db) << '\n';
  }

  if (sqlite3_finalize(stmt) != SQLITE_OK)
  {
    std::cerr << "Failure finalizing [" << request << "]:\n\t"
              << sqlite3_errmsg(_db) << '\n';
  }
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
  DbTableGrammarExamples tableCol;
  row[tableCol.id_rule] = std::stoi(argv[0]);
  row[tableCol.id_word] = std::stoi(argv[1]);

  return 0;
}
