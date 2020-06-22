#ifndef DB_HH_
# define DB_HH_

# include <string>

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
   * @brief Get every words, sorted alphabetically
   * @param cb Callback function
   * @param first first result
   * @warning throws
   */
  static void getWordsSorted(int (*cb) (void*, int, char**, char**),
                             void *first);

  /**
   * @brief Get a specific word
   * @param word_id id of the word to fetch
   * @param first first result
   * @warning throws
   */
  static void getWord(int word_id, void *first);

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


  static int dbFetchWords(void *model, int argc, char **argv, char **azColName);

  static int fetchTranslations(void *model, int argc, char **argv, char **azColName);



private:
  static sqlite3 *_db; ///< Database
};

#endif /* !DB_HH_ */
