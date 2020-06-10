#include <iostream>

extern "C" {
#include <lib/sqlite3.h>
}


int main()
{
  sqlite3 *db;
  if (sqlite3_open("/", &db))
  {
    std::cerr << "Failure opening DB:\n\t" << sqlite3_errmsg(db) << '\n';
    return 1;
  }

  std::cout << "DB OPENED\n";
  sqlite3_close(db);
}
