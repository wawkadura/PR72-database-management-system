#include "select_query.h"
#include "error/query_error_exception.h"

using namespace std;

SelectQuery::SelectQuery(std::string query, DbInfo db):SqlQuery(db){
    SelectQuery::parse(query);
}
void SelectQuery::parse(string user_sql) {
    sqlDetails.primaryCommand = "SELECT";

    string upperCaseSQL = SqlQuery::parseToUpper(user_sql);

    int fromIndex = upperCaseSQL.find("FROM");
    if (fromIndex=std::string::npos) {
        cout << "Mauvaise requête" << endl;
        throw(QueryErrorException("Missing FROM"));
    }
    string columns = user_sql.substr(0, fromIndex-1);
    remove(columns.begin(), columns.end(), ' ');
    // map<string, string> columnsMap;
    // split columns by , loop in and push_back in map


    sqlDetails.table = TableFile(user_sql.substr(fromIndex+1, user_sql.find(' ',fromIndex)));

    int whereIndex = upperCaseSQL.find("WHERE");
    sqlDetails.conditions = user_sql.substr(whereIndex+1);


}
void SelectQuery::check() {}
void SelectQuery::execute(){}
void SelectQuery::expand(){}