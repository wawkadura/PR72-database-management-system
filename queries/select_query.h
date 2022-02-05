#ifndef SELECT_QUERY_H
#define SELECT_QUERY_H

#include "sql_query.h"

class SelectQuery : public SqlQuery {
private:

public:
    SelectQuery();
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
    void expand();
};

#endif