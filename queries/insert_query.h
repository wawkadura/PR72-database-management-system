#ifndef INSERT_QUERY_H
#define INSERT_QUERY_H

#include "sql_query.h"

class InsertQuery : public SqlQuery {
private:

public:
    InsertQuery();
    virtual void parse(std::string user_sql) void;
    virtual void execute() void;
};

#endif