#include "insert_query.h"
#include "../error/query_error_exception.h"
#include "key_file.h"
#include "sql_query.h"

using namespace std;

InsertQuery::InsertQuery(string query, DbInfo db):SqlQuery(db){
    InsertQuery::parse(query);
}

char *get_sep_space(char *sql) {
    while(isspace(*sql)) {
        sql++;
    }
    return sql;
}

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

bool has_reached_sql_end(char *sql) {
    sql=get_sep_space(sql);
    if (*sql == '\0' || *sql == ';') {
        return true;
    }else{
        return false;
    }
}

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
            throw(QueryErrorException("error2"));;
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

char *parse_fields_or_values_list(char *sql, table_record_t *result) {
    
    char field[TEXT_LENGTH];

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

            if(sql == NULL){
                return NULL;
            }

            //check the type of the field and add it to the list

            result->fields[result->fields_count].field_type = TYPE_UNKNOWN;
            strcpy(result->fields[result->fields_count].field_value.text_value, field);

            result->fields_count++;

            //if there is a comma, the list of values or fields names continues, otherwise it is the end of the list
            if (get_sep_space_and_char(sql, ',') != NULL) {
                sql = get_sep_space_and_char(sql, ',');
            } else {
                continue_parsing = false;
            }

        }
        
    }

    if(sql == NULL){
        return NULL;
    }
    //if there is a parenthesis, the list of values or fields names must end with a parenthesis
    if(get_sep_space_and_char(sql, ')') != NULL && parenthesis_opened) {
        sql = get_sep_space_and_char(sql, ')');
        return sql;
    }else if (!parenthesis_opened) {
        return sql;
    }else if (parenthesis_opened) {
        printf("Error: Expected ')'\n");
        return NULL;
    }else{
        printf("Error: Unexpected ')'\n");
        return NULL;
    }
}

void InsertQuery::parse(char *user_sql) {

     //intialize the result
    result->query_content.insert_query.fields_values.fields_count = 0;
    result->query_content.insert_query.fields_names.fields_count = 0;

    result->query_type = QUERY_INSERT;
    if (has_reached_sql_end(user_sql)) {
        throw(QueryErrorException("Directory doesn't exist!"));;
    }
    user_sql = get_keyword(user_sql, "into");
    if(user_sql == NULL){
        throw(QueryErrorException("Error: missing INTO keyword"));;
    }
    if (has_reached_sql_end(user_sql)) {
        throw(QueryErrorException("Directory doesn't exist!"));;
    }
    user_sql= get_field_name(user_sql, result->query_content.insert_query.table_name);
    if(user_sql == NULL){
        throw(QueryErrorException("Directory doesn't exist!"));;
    }
    if (has_reached_sql_end(user_sql)) {
        throw(QueryErrorException("Directory doesn't exist!"));;
    }
    
    if(get_keyword(user_sql, "values") == NULL){
        user_sql = parse_fields_or_values_list(user_sql, &result->query_content.insert_query.fields_names);
        if(user_sql == NULL){
            throw(QueryErrorException("Directory doesn't exist!"));;
        }  
        if (has_reached_sql_end(user_sql)) {
            throw(QueryErrorException("Directory doesn't exist!"));;
        }
    }else{

        result->query_content.insert_query.fields_names.fields_count = 1;
        result->query_content.insert_query.fields_names.fields[0].field_type = TYPE_TEXT;
        strcpy(result->query_content.insert_query.fields_names.fields[0].field_value.text_value, "*");

    }
    user_sql = get_keyword(user_sql, "values");
    if(user_sql == NULL){
        throw(QueryErrorException("Error: missing VALUES keyword"));;
    }
    if (has_reached_sql_end(user_sql)) {
        throw(QueryErrorException("error19"));;
    }
    user_sql = parse_fields_or_values_list(user_sql, &result->query_content.insert_query.fields_values);
    if(user_sql == NULL){
        throw(QueryErrorException("list value"));;
    }
    if (has_reached_sql_end(user_sql)) {
        return result;
    }else{
        throw(QueryErrorException("errr20"));;
    }
};
    

void InsertQuery::check() {}
void InsertQuery::execute(){
    // //manage key file 
    // for (int i = 0; i < query->fields_values.fields_count; i++)
    // {   
    //     if(query->fields_values.fields[i].field_type == TYPE_PRIMARY_KEY){
    //         unsigned long long next_key = get_next_key(query->table_name);
    //         if( query->fields_values.fields[i].field_value.primary_key_value > next_key){
    //             update_key(query->table_name, query->fields_values.fields[i].field_value.primary_key_value);
    //         } else {
    //             query->fields_values.fields[i].field_value.primary_key_value = next_key;
    //             update_key(query->table_name, next_key++);
    //         }
    //     }  
    // }
    // //add value
    // add_row_to_table(query->table_name, &query->fields_values);
}


