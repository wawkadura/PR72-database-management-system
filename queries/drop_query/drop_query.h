#ifndef DROP_QUERY_H
#define DROP_QUERY_H

#include "drop_query.h"

class DropQuery {
private:

public:
    DropQuery();
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif