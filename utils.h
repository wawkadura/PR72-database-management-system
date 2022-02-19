#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <map>
#include <sstream>


using namespace std;
enum field_types
{
    TYPE_UNKNOWN,
    TYPE_PRIMARY_KEY,
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_TEXT
};

struct field_definition
{
    std::string field_name;
    field_types field_type;
};

struct table_definition
{
    int fields_count;
    std::vector<field_definition> definitions;
    
    string toString(){
        string field_names;
        for (field_definition name : definitions)
            field_names += name.field_name + " ";
        return field_names;
    }
};

struct field_values
{
    unsigned long primary_key_value;
    int int_value;
    double float_value;
    std::string text_value;
};

struct field_record
{
    std::string field_name;
    field_types field_type;
    field_values field_value;
};

struct table_records
{
    int fields_count;
    std::vector<field_record> fields;
    string toString(){
        string field_names;
        for (field_record rec : fields)
            field_names += rec.field_name + " ";
        return field_names;
    }
};

struct index_entry
{
    int field_type_t;
    std::vector<field_definition> field_type;
};

// check if field is in table def
field_definition *find_field_definition(string field_name, table_definition *table_definition) {
    for( field_definition &field : table_definition->definitions ){
        if(field.field_name.compare(field_name) == 0){
            return &field;
        }
    }
    return NULL;     
}

// check if all the fields exist in table def
bool checkFields(table_records fields_list, table_definition table_definition) {
    cout << "checking fields :" << fields_list.toString() << " in " << table_definition.toString() << endl;
    for (field_record rec : fields_list.fields)
    {
        if(rec.field_name == "\0"){
            rec.field_name = rec.field_value.text_value;
        }
        if(find_field_definition(&rec.field_name[0], &table_definition)==NULL){
           return false;
        }
    }
    return true;
}

// check if a string is included in the given vector<string>
bool includedIn(string s, vector<string> ss)
{
    for (int i = 0; i < ss.size(); i++)
        if (s == ss.at(i))
            return true;

    return false;
}

// split a given string by a given delimiter
vector<string> Split(const std::string &s, char delimiter)
{
    vector<string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// count the number of occurences of the given character in the given word
int count(string s, char ch)
{
    int count = 0;

    for (int i = 0; (i = s.find(ch, i)) != std::string::npos; i++)
    {
        count++;
    }

    return count;
}

bool isOperator(string s)
{
    const map<string, bool> operators{
        {"=", true},
        {"!=", true},
        {"<", true},
        {">", true},
        {"<=", true},
        {">=", true},
    };
    auto itr = operators.find(s);

    if (itr != operators.end())
        return itr->second;

    return false;
}

std::string toUpper(std::string text){
    std::transform(
        text.begin(), 
        text.end(), 
        text.begin(),
        [](unsigned char c)
        { return std::toupper(c); }
    );
    return text;
};


table_records mapToRecords(map<string, string> ss)
{
    table_records tabRecords;
    map<string, string>::iterator it;
    std::vector<field_record> fields;

    for (it = ss.begin(); it != ss.end(); it++)
    {
        field_values fv = {text_value : it->second};
        field_record f = {field_name : it->first, field_value : fv};
        fields.push_back(f);
    }
    tabRecords.fields = fields;

    return tabRecords;
}

std::string removeChar(std::string s, char c){
    vector<string> ss = Split(s, c);
    string newString = "";
    for(auto var : ss)
    {
        newString+=var;
    }

    return newString;
}

struct insert_query {
    const char *table_name;
    std::string field_name;
    field_types field_type;
};

struct insert_records {
    int fields_count;
    std::vector<insert_query> fields;
};

struct query_result {
    insert_query insert;
    std::vector<insert_query> query_content;
};

#endif

