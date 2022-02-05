#ifndef QUERY_FACTORY_H
#define QUERY_FACTORY_H

#include <iostream>
#include <algorithm>

#include "sql_query.h"
#include "db_info.h"

using namespace std;

// Design pattern factory
class QueryFactory 
{ 
  public :
    QueryFactory();
    Command resolveCommand (std::string input);
    static SqlQuery* generate_query(std::string sql, DbInfo db);
}

enum Command { SELECT, CREATE, INSERT, UPDATE, DELETE, DROP, INVALID };

#endif