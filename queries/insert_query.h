#ifndef INSERT_QUERY_H
#define INSERT_QUERY_H
#include "sql_query.cpp"
#include "../db_info.cpp"

class InsertQuery : public SqlQuery {
private:
    
public:
    InsertQuery(std::string query, DbInfo db);
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif