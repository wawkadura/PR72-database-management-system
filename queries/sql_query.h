#include <iostream>
#include "db_info.h"
#include "table_file.h"

class SqlQuery {
private:
	std::string query;
    DbInfo db;
    TableFile table;
public:
    SqlQuery();
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
    Array<SqlRow> where();
    std::string getQuery() const {return query;};
    ~SqlQuery(){};
};
