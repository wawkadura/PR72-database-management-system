#ifndef INSERT_QUERY_H
#define INSERT_QUERY_H

#include "sql_query.h"

class InsertQuery : public SqlQuery {
private:
    
public:
    InsertQuery(std::string query, DbInfo db);
    virtual query_result *parse(string user_sql,query_result *result);
    virtual void check();
    virtual void execute(insert_query *query);
};

#endif