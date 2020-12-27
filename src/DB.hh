#ifndef DB_HH_
# define DB_HH_

# include <string>
# include <vector>

struct sqlite3;

/**
 * @class DB
 * @brief Sqlite database handling
 * @note Static class
 */
class DB
{
public:
  /**
   * @brief Opens the database
   * @param file_name Database file to open
   * @warning throws
   */
  static void initialize(const std::string file_name);

  /**
   * @brief Get the full content of the given table
   * @param table Concerned table name
   * @param first First result
   * @return Table second column content as strings
   * @warning The table must have 2 columns minimum
   * @warning throws
   */
  static std::vector<std::string> getTableEntries(const std::string &table);

  /**
   * @brief Edit the given word
   * @param id Id of the word to edit
   * @param name Word text
   * @param language Valid foreign key to a 'languages' table entry
   * @param category Valid foreign key to a 'categories' table entry
   * @return true on success; false otherwise (ex: invalid language / category)
   */
  static bool editWord(int id, const std::string& name, int language, int category);

  /**
   * @brief Add a word in the Words table
   * @param name Word text
   * @param language Valid foreign key to a 'languages' table entry
   * @param category Valid foreign key to a 'categories' table entry
   * @return true on success; false otherwise (ex: invalid language / category)
   */
  static bool addWord(const std::string& name, int language, int category);

  /**
   * @brief Get every words, sorted alphabetically
   * @param language_id Language to retrieve the words from
   * @param first First result
   * @param filter Eventual filter on the name (used with words.name LIKE filter)
   * @warning throws
   */
  static void getWordsLanguageSortedName(int language_id,
                                         void *first,
                                         const std::string filter = "");

  /**
   * @brief Get every words, sorted by insertion date
   * @param language_id language to retrieve the words from
   * @param first first result
   * @warning throws
   */
  static void getWordsLanguageSortedInsertionDate(int language_id, void *first);

  /**
   * @brief Get a specific word
   * @param word_id id of the word to fetch
   * @param first first result
   * @warning throws
   */
  static void getWord(int word_id, void *first);

  /**
   * @brief Get the grammar titles
   * @param first first result
   * @warning throws
   */
  static void getGrammarRulesTitles(void *first);

  /**
   * @brief Get the translations of the give word
   * @param cb Callback function
   * @param first first result
   * @warning throws
   */
  static void getTranslations(int word_src_id,
                              int (*cb) (void*, int, char**, char**),
                              void *first);

  /**
   * @brief Get the examples of the given grammar rule
   * @param grammar_rule_id Grammar rule id (in DB grammar_rules table)
   * @param first first result
   * @warning throws
   */
  static void getGrammarExamples(int grammar_rule_id, void *first);

  /**
   * @brief Wrapper around sqlite3_exec
   * @param request Raw SQL request string
   * @param cb Callback function
   * @param first First callback argument
   */
  static void rawRequest(const std::string request,
                         int (*cb) (void*, int, char**, char**),
                         void *first);

  /**
   * @brief Properly close the Database file
   */
  static void close();


  static int fetchTranslations(void *model, int argc, char **argv, char **azColName);



private:
  static int dbFetchWords(void *model, int argc, char **argv, char **azColName);

  static int fetchGrammarRulesTitles(void *model, int argc, char** argv, char **azColName);
  static int fetchGrammarExamples(void *model, int argc, char** argv, char **azColName);


  static sqlite3 *_db; ///< Database
};

#endif /* !DB_HH_ */
