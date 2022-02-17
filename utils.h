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

#endif

