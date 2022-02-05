#ifndef DELETE_QUERY_H
#define DELETE_QUERY_H

#include "sql_query.h"

class DeleteQuery : public SqlQuery {
private:

public:
    DeleteQuery();
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif