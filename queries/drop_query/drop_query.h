#ifndef DROP_QUERY_H
#define DROP_QUERY_H

#include "../sql_query.h"
// #include "../../db_info.cpp"

class DropQuery : public SqlQuery {
private:

public:
    DropQuery();
    DropQuery(DbInfo db);
    DropQuery(std::string query, DbInfo db);
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif