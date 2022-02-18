#ifndef QUERY_FACTORY_H
#define QUERY_FACTORY_H

#include <iostream>
#include <algorithm>

#include "sql_query.h"
#include "select_query.cpp"
#include "update_query/update_query.cpp"
#include "../db_info.h"

using namespace std;

enum Command { SELECT, CREATE, INSERT, UPDATE, DELETE, DROP, INVALID };

// Design pattern factory
class QueryFactory 
{ 
  public :
    QueryFactory();
    Command resolveCommand (std::string input);
    SqlQuery* generate_query(std::string sql, DbInfo db);
};


#endif