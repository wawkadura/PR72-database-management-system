#include "delete_query.h"

using namespace std;

DeleteQuery::DeleteQuery(std::string query, DbInfo db):SqlQuery( db){
    DeleteQuery::parse(query);
}
void DeleteQuery::parse(string user_sql) {}
void DeleteQuery::check() {
    this->sqlDetails.table.exist();
}
void DeleteQuery::execute(){}
