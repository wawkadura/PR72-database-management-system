#ifndef DROP_TABLE_QUERY_H
#define DROP_TABLE_QUERY_H

#include "drop_query.h"
#include <string>

class DropTableQuery : public DropQuery {
private:

public:
    DropTableQuery(std::string query, DbInfo db);
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif