#ifndef INSERT_QUERY_H
#define INSERT_QUERY_H
#include "sql_query.cpp"
#include "../table_file/key_file.h"
#include "../utils.h"

class InsertQuery : public SqlQuery
{
private:

protected:
    std::vector<string> values;

public:
    InsertQuery(std::string query, DbInfo db);
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif