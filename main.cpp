#include <iostream>
#include "db_info.cpp"
#include "queries/query_factory.cpp"
#include "utils.h"
#include <map>

int main()
{
    DbInfo db("e");
    std::string query = "select     test, testtl, smeo, stev from twerlik";
    QueryFactory factory;
    SqlQuery* sq = factory.generate_query(query, db);
    sq->check();
    // loop
    /* code */
    return 0;
}
