#include "select_query.h"
#include "error/query_error_exception.h"

using namespace std;

SelectQuery::SelectQuery(std::string query, DbInfo db):SqlQuery(db){
    SelectQuery::parse(query);
}


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

/**
 * @brief Get the first occurrence of a non space character in a string.
 * @example "   hello" -> pointer to "hello"
 * 
 * @param sql Pointer to a position in the sql query.
 * @return char* Return the pointer to the first occurrence of a non space character.
 */
char *get_sep_space(char *sql) {
    /*if(!isspace(*sql)) {
        printf("Use less \n");
    }*/
    //debug code
    while(isspace(*sql)) {
        sql++;
    }
    return sql;
}

/**
 * @brief Check if it is the end of the query by looking if there are only spaces left.
 * 
 * @param sql Pointer to a position in the sql query.
 * @return true If it is the end of the query.
 * @return false If it is not the end of the query.
 */
bool has_reached_sql_end(char *sql) {


    sql=get_sep_space(sql);

    if (*sql == '\0' || *sql == ';') {
        return true;
    }else{
        return false;
    }
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