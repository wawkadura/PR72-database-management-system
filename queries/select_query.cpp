#include "select_query.h"
#include "../error/query_error_exception.h"

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
    std::cout << "parse SELECT : SELECT " << user_sql << endl;
    sqlDetails.primaryCommand = "SELECT";

    string upperCaseSQL = SqlQuery::parseToUpper(user_sql);

    int fromIndex = upperCaseSQL.find("FROM");
    if (fromIndex==std::string::npos) {
        cout << "Mauvaise requete" << endl;
        throw(QueryErrorException("Missing FROM"));
    }

    string columns = user_sql.substr(0, fromIndex-1);
    // remove spaces
    string::iterator end_pos = remove(columns.begin(), columns.end(), ' ');
    columns.erase(end_pos, columns.end());

    // split columns by , loop in and push_back in map
    table_records tabRecords;
    stringstream ss(columns);
    string col;
    while (getline(ss, col, ',')) {
        // field_values a = {0,0,0,col};
        // field_record b = {col,field_types(4),a};
        tabRecords.fields.push_back({col,field_types(4),{0,0,0,col}});
    }
    sqlDetails.tabRecords = tabRecords;

    // get table name
    int fromEndIndex = fromIndex + 5;
    int spaceAfterTableIndex = user_sql.find(' ',fromEndIndex);
    sqlDetails.table = TableFile(user_sql.substr(fromEndIndex, spaceAfterTableIndex-fromEndIndex));

    // get conditions
    int whereIndex = upperCaseSQL.find("WHERE");
    if (whereIndex!=std::string::npos) {
        sqlDetails.conditions = user_sql.substr(whereIndex+6);
    }


    cout << "---------------" << endl << sqlDetails.toString() << endl << "---------------" << endl;
    cout << "END parse SELECT" << endl;
}

field_definition *find_field_definition(string field_name, table_definition *table_definition) {
    for(int i=0; i < table_definition->fields_count; i++){
        if(table_definition->definitions[i].field_name.compare(field_name) == 0){
            return &table_definition->definitions[i];
        }
    }
    return NULL;     
}

bool check_fields_list(table_records fields_list, table_definition table_definition) {
    for (size_t i = 0; i < fields_list.fields_count; i++)
    {
        if(fields_list.fields[i].field_name == "\0"){
            fields_list.fields[i].field_name = fields_list.fields[i].field_value.text_value;
        }
        if(find_field_definition(&fields_list.fields[i].field_name[0], &table_definition)==NULL){
           return false;
        }
    }
    return true;
}

void SelectQuery::check() {
    this->sqlDetails.toString();
    this->sqlDetails.table.exist();
    bool check = check_fields_list(this->sqlDetails.tabRecords, this->sqlDetails.tableDef.get_table_definition());
    if (check != false) {
    	cout << "Fields not corresponding!";
        throw(QueryErrorException("Fields not corresponding!"));
    }
}




void SelectQuery::execute(){}
void SelectQuery::expand(){}