#include <iostream>
#include <stdexcept>

#include <DB.hh>

extern "C" {
#include <lib/sqlite3.h>
}


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



void DB::getWordsSorted(int (*cb) (void*, int, char**, char**),
                        void *first)
{
  const char *request = "SELECT * FROM words ORDER BY name ASC";
  rawRequest(request, cb, first);
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
