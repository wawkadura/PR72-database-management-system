#include "insert_query.h"
#include "../error/query_error_exception.h"
#include "../table_file/key_file.h"
#include "sql_query.h"

using namespace std;

InsertQuery::InsertQuery(string query, DbInfo db):SqlQuery(db){}

char *get_sep_space(char *sql) {
    while(isspace(*sql)) {
        sql++;
    }
    return sql;
}

/**
 * @brief Get the first occurrence of a character after spaces and one time the parameter "c".
 * @example "  ,  id WHERE data = 2 , id = 1",',' -> pointer to "id WHERE data = 2 , id = 1"
 * @example "  a  data , id",'a' -> pointer to "data , id"
 */
char *get_sep_space_and_char(char *sql, char c) {
    sql = get_sep_space(sql);
    //check if the character is present
    if (*sql == c) {
        sql++;
    }else{
        return NULL;
    }
    sql=get_sep_space(sql);
    return sql;
}
/**
 * @brief Check if it is the end of the query by looking if there are only spaces left.
 * @param sql Pointer to a position in the sql query.
 */
bool has_reached_sql_end(char *sql) {
    sql=get_sep_space(sql);
    if (*sql == '\0' || *sql == ';') {
        return true;
    }else{
        return false;
    }
}

/**
 * @brief Get the field name object.
 * @example "'my name is' text)" -> " text" and field_name = "my name is"
 */
char *get_keyword(char *sql, char *keyword) {
    bool valid = true;
    sql=get_sep_space(sql);
    //check if the keyword is present
    while(valid && *keyword != '\0') {
        if (tolower(*sql) != tolower(*keyword)) {
            valid = false;
        }
        sql++;
        keyword++;
    }
    if (valid) {
        return sql;
    }else{
        throw(QueryErrorException("error1"));;
    }
}

char *get_field_name(char *sql, char *field_name) {
    int i = 0;
    sql=get_sep_space(sql);

    //if there is a ' character the field name is between ' and '
    if (*sql== '\'') {
        i++;
        sql++;
        while(*sql != '\'' && *sql != '\0') {
            field_name[i-1] = *sql;
            i++;
            sql++;
        }
        if(*sql == '\0') {
            throw(QueryErrorException("error missin ''"));;
        }
        field_name[i-1] = '\0';
        return ++sql;
    }else{
        //if there is not a ' character the field name continues until the next non alphanumeric character or _
        while(isalnum(*sql) || *sql == '_' || *sql == '.' || *sql == '-') {
            field_name[i] = *sql;
            i++;
            sql++;
        }
        field_name[i] = '\0';
        if(field_name[0] == '\0') {
            throw(QueryErrorException("error3"));;
        }
        return sql;
    }
}
/**
 * @brief Get a list of value or fiels names.
 * @example " id, name, age WHERE id=2;" -> "WHERE id=2;" and result->fields_count = 3 result->fields[0] = TYPE_TEXT,"id" result->fields[1] = TYPE_TEXT,"name" result->fields[2] = TYPE_TEXT,"age"
 * @example "12, Hey, 2.5 WHERE id=2;" -> "WHERE id=2;" and result->fields_count = 3 result->fields[0] = TYPE_INTEGER,"12" result->fields[1] = TYPE_TEXT,"Hey" result->fields[2] = TYPE_FLOAT,"2.5"
 * @param sql Pointer to a position in the sql query.
 * @param result a pointer to the list of values or fields names in an organised structure to modificate.
 */  
char *parse_fields_or_values_list(char *sql,  insert_records *result) {
    char *field;
    bool continue_parsing = true;
    bool parenthesis_opened = false;

    sql= get_sep_space(sql);

    //If there is a parenthesis, the list of values or fields names is between parenthesis
    if(*sql=='(') {
        sql++;
        parenthesis_opened = true;
    }

    while (continue_parsing)
    {
        if (has_reached_sql_end(sql)) {
            continue_parsing = false;
        }else{
            sql= get_field_name(sql, field);

            //check the type of the field and add it to the list

            result->fields[result->fields_count].field_type = TYPE_UNKNOWN;
            char* values = const_cast<char*>((result->fields[result->fields_count].field_value.text_value).c_str());//convert string into char *
            strcpy(values, field);

            result->fields_count++;

            //if there is a comma, the list of values or fields names continues, otherwise it is the end of the list
            if (get_sep_space_and_char(sql, ',') != NULL) {
                sql = get_sep_space_and_char(sql, ',');
            } else {
                continue_parsing = false;
            }

        }
        
    }

    //if there is a parenthesis, the list of values or fields names must end with a parenthesis
    if(get_sep_space_and_char(sql, ')') != NULL && parenthesis_opened) {
        sql = get_sep_space_and_char(sql, ')');
        return sql;
    }else if (!parenthesis_opened) {
        return sql;
    }else if (parenthesis_opened) {
        throw(QueryErrorException("Error: Expected ')'"));;
    }else{
        throw(QueryErrorException("Error: Unexpected ')"));;
    }
}

/**
 * @brief function that extract the data from a sql insert query.
 * @param sql Pointer to the sql insert query without INSERT.
 * @param result Pointer to the data structure to modificate.
 */
query_result *InsertQuery::parse(string user_sql, query_result *result) {

    char* the_sql = const_cast<char*>((user_sql).c_str());//convert string into char *
    if (has_reached_sql_end(the_sql)) {
        throw(QueryErrorException("Query not well made end"));;
    }
    the_sql = get_keyword(the_sql, "into");
    if(the_sql == NULL){
        throw(QueryErrorException("Error: missing INTO keyword"));;
    }
    if (has_reached_sql_end(the_sql)) {
        throw(QueryErrorException("Query not well made end"));;
    }
    the_sql= get_field_name(the_sql, result->query_content.insert_query.table_name);
    if(the_sql == NULL){
        throw(QueryErrorException("Error in feld name"));;
    }
    if (has_reached_sql_end(the_sql)) {
        throw(QueryErrorException("Query not well made end"));;
    }
    
    if(get_keyword(the_sql, "values") == NULL){
        the_sql = parse_fields_or_values_list(the_sql, &result->query_content.insert_query.fields_names);
        if(the_sql == NULL){
            throw(QueryErrorException("Missing 'values' required"));;
        }  
        if (has_reached_sql_end(the_sql)) {
            throw(QueryErrorException("Query not well made end"));;
        }
    }else{

        result->query_content.insert_query.fields_names.fields_count = 1;
        result->query_content.insert_query.fields_names.fields[0].field_type = TYPE_TEXT;
        strcpy(result->query_content.insert_query.fields_names.fields[0].field_value.text_value, "*");

    }
    the_sql = get_keyword(the_sql, "values");
    if(the_sql == NULL){
        throw(QueryErrorException("Error: missing VALUES keyword"));
    }
    if (has_reached_sql_end(the_sql)) {
        throw(QueryErrorException("Query not well made end"));
    }
    the_sql = parse_fields_or_values_list(the_sql, &result->query_content.insert_query.fields_values);
    if(the_sql == NULL){
        throw(QueryErrorException("list value"));
    }
    if (has_reached_sql_end(the_sql)) {
        return result;
    }else{
        throw(QueryErrorException("Query not well made end"));
    }
};


void InsertQuery::check() {}

void InsertQuery::execute(insert_query *query) {
    
    // //key file(primary key )
    // for (int i = 0; i < query->fields_values.fields_count; i++)
    // {   
    //     if(query->fields_values.fields[i].field_type == TYPE_PRIMARY_KEY){
    //         unsigned long long next_key = this->sqlDetails.key.get_next_key(query->table_name);
    //         if( query->fields_values.fields[i].field_value.primary_key_value > next_key){
    //             this->sqlDetails.key.update_key(query->table_name, query->fields_values.fields[i].field_value.primary_key_value);
    //         } else {
    //             query->fields_values.fields[i].field_value.primary_key_value = next_key;
    //             this->sqlDetails.key.update_key(query->table_name, next_key++);
    //         }
    //     }  
    // }

    // //write to content file
    // table_definition  def = this->sqlDetails.tableDef.get_table_definition();
    // int sizeIndex = this->index->size();
    // int sizeContent = this->content->size();
    // index_entry entry = {true};
    // Buffer buf = query_to_content(query,def);
    // this->sqlDetails.index.write_index_entry(entry,sizeIndex);
    // this->sqlDetails.content.write_record(buf,sizeContent);
    
}
