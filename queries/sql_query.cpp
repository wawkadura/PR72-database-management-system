#include "sql_query.h"

// SqlQuery::SqlQuery(std::string _query, DbInfo _db, TableFile _table):query(_query), db(_db), table(_table){};

SqlQuery::SqlQuery(DbInfo _db): db(_db) {};

SQLDETAILS SqlQuery::getSqlDetails() {
    return SqlQuery::sqlDetails;
};

std::string SqlQuery::parseToUpper(std::string text){
    std::transform(
        text.begin(), 
        text.end(), 
        text.begin(),
        [](unsigned char c)
        { return std::toupper(c); }
    );
    return text;
};

