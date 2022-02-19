#ifndef CREATE_TABLE_QUERY_H
#define CREATE_TABLE_QUERY_H

#include "../sql_query.h"

class CreateTableQuery : public SqlQuery {
private:
    table_definition tb;
public:
    CreateTableQuery(std::string query, DbInfo db);
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif