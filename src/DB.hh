#ifndef DB_HH_
# define DB_HH_

# include <string>


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
   * @warning throws
   */
  static void getWordsSorted();


  /**
   * @brief Wrapper around sqlite3_exec
   * @param request Raw SQL request string
   * @param cb Callback function
   * @param first First callback argument
   */
  static void rawRequest(const std::string request,
                         int (*cb) (void*, int, char**, char**),
                         void *first);
};

#endif /* !DB_HH_ */
