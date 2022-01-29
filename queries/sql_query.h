#include <iostream>

class SqlQuery {
private:
	string query;
    DbInfo db;
    TableFile table;
public:
    SqlQuery();
    virtual void parse(std::string user_sql);
    virtual void check();
    virtual void execute();
    array<SqlRow> where(){

    };
    string getQuery() const {return query;};
    ~SqlQuery(){};
};
