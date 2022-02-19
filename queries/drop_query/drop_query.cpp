#include "drop_query.h"

using namespace std;

DropQuery::DropQuery(DbInfo db): SqlQuery(db){}

void DropQuery::parse(std::string user_sql){};
void DropQuery::check(){};
void DropQuery::execute(){};