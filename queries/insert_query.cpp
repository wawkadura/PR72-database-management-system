#include "insert_query.h"

using namespace std;

InsertQuery::InsertQuery(std::string query, DbInfo db):SqlQuery(db){}
void InsertQuery::parse(string user_sql) {}
void InsertQuery::check() {}
void InsertQuery::execute(){}