#include "update_query.h"
#include <sstream>
#include <string>
#include <vector>
#include "error/query_error_exception.h"
#include <map>

using namespace std;

UpdateQuery::UpdateQuery(std::string query, DbInfo db) : SqlQuery::SqlQuery(db)
{
    UpdateQuery::parse(query);
}

// table SET (setters >= 1) WHERE (conditions >=1)
// [table, SET, setter1, ',' , setter2,  WHERE, condition1, and/or, condition2,  ; ]
void UpdateQuery::parse(string user_sql)
{
    sqlDetails.primaryCommand = "UPDATE";
    string set = "SET";
    string where = "WHERE";
    string end = ";";
    vector<string> options = {set, where, end};

    vector<string> words;
    istringstream iss(user_sql);
    do
    {
        string word;
        iss >> word;
        words.push_back(word);
    } while (iss);

    // Check the minimum requirement of words
    if (words.size() < 5)
    {
        throw(QueryErrorException("Syntaxe error : make sure to put spaces between arguments"));
    }

    // Check SET
    int position = 0;
    if (position >= words.size() || parseToUpper(words[++position]) != set)
        throw(QueryErrorException("missing SET"));

    // Check Setters
    vector<string> setters;

    for (int i = ++position; i < words.size(); i++)
    {
        if (notIncludedIn(parseToUpper(words[i]), options, 3))
        {
            setters.push_back(words[i]);
        }
        else
        {
            position = i;
            break;
        }
    }

    if (setters.size() < 1)
        throw(QueryErrorException("missing setters"));

    if (!validateSetters(setters, sqlDetails.columnsMapper))
        throw(QueryErrorException("error in setters syntax"));

    // Check WHERE
    if (position >= words.size() || parseToUpper(words[position]) != where)
        throw(QueryErrorException("missing where clause"));

    // Check conditions
    vector<string> conditions;

    for (int i = ++position; i < words.size(); i++)
    {
        if (notIncludedIn(parseToUpper(words[i]), options, 3))
        {
            conditions.push_back(words[i]);
        }
        else
        {
            position = i;
            break;
        }
    }

    if (!validateConditions(conditions))
        throw(QueryErrorException("error in where conditions syntax"));

    // Check for the ';'
    if (position >= words.size() || parseToUpper(words[position]) != end)
        throw(QueryErrorException("error syntax : missing the ';' at the end of the query "));
}
void UpdateQuery::check() {}
void UpdateQuery::execute() {}


// SET id = 5 , name="walid", number=06123456789,address="Belfort"

bool validateSetters(vector<string> setters, map<string, string> &mapper)
{
    vector<string> formatedSetters = formatSetters(setters);
    for (int i = 0; i < formatedSetters.size(); i++)
    {
        bool ok = setColumn(formatedSetters[i], mapper);
        if (!ok)
            return false;
    }
    return true;
}


// Expected : ['id', '=', '5', ',' , 'name="walid",' , 'number=06123456789,address="Rue,Belfort"']
// Return : [id=5, name="walid", number="06123456789", address="Rue,Belfort" ]

// TODO: implimente body
bool validateConditions(vector<string> setters)
{
    return false;
}

vector<string> formatSetters(vector<string> setters)
{
    // CURRENTLY: ['id', '=', '5', ',' , 'name="walid",' , 'number=06123456789,address="Rue,Belfort"']
    string words;
    for (int i = 0; i < setters.size(); i++)
    {
        words = "" + (setters[i]);
    }
    // CURRENTLY: 'id=5,name="walid",number=06123456789,address="Belfort"'

    vector<string> splittedWords = Split(words, ',');
    // CURRENTLY: ['id=5' , 'name="walid"', 'number=06123456789','address="Rue,Belfort"']

    vector<string> finalFormat;
    string s;
    for (int i = 0; i < splittedWords.size(); i++)
    {
        if (Count(splittedWords[i], '"') == 1)
        {
            if (s != "")
            {
                s = s + "," + splittedWords[i];
                finalFormat.push_back(s);
                s = "";
            }
            else
            {
                s = splittedWords[i];
            }
        }
        else
        {
            finalFormat.push_back(splittedWords[i]);
        }
    }

    return finalFormat;
}

// Expected : "id=5"
// Result : {"id" : "5"}
bool setColumn(string s, map<string, string> &m)
{
    vector<string> ss = Split(s, '=');
    if(ss.size()!= 2) return false;
    m.insert(ss[0],ss[1]);
}

bool isOperator(string s)
{
    auto itr = operators.find(s);

    if (itr != operators.end())
        return itr->second;

    return false;
}

static const map<string, bool> operators{
    {"=", true},
    {"!=", true},
    {"<", true},
    {">", true},
    {"<=", true},
    {">=", true},
};

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
int Count(string s, char ch)
{
    int count = 0;

    for (int i = 0; (i = s.find(ch, i)) != std::string::npos; i++)
    {
        count++;
    }

    return count;
}

bool notIncludedIn(string s, vector<string> ss, int size)
{
    for (int i = 0; i < size; i++)
        if (s == ss.at(i))
            return true;

    return false;
}