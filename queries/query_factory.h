#ifndef QUERY_FACTORY_H
#define QUERY_FACTORY_H
#include "db_info.h"
#include <iostream>

using namespace std;

// Design pattern factory
class QueryFactory 
{ 
  public :
    Command resolveCommand (std::string input);
    static SqlQuery* generate_query(std::string sql, DbInfo db);
}

enum Command { SELECT, CREATE, INSERT, UPDATE, DELETE, DROP, INVALID };

#endif