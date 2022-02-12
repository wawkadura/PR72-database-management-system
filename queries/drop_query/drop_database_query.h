#ifndef DROP_DATABASE_QUERY_H
#define DROP_DATABASE_QUERY_H
#include <string>
#include "drop_query.h"

class DropDatabaseQuery : public DropQuery {
private:

public:
    DropDatabaseQuery();
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
};

#endif