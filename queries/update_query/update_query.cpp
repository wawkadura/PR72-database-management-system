#include "update_query.h"
#include <string>
#include <vector>
#include "../sql_query.cpp"
#include <iostream>
#include "../../utils.h"
#include "../../error/query_error_exception.cpp"
#include <map>

using namespace std;

// // TODO: implimente body
bool validateConditions(vector<string> setters)
{
    return true;
}

// Expected : ['id', '=', '5', ',' , 'name="walid",' , 'number=06123456789,address="Rue,Belfort"']
// Return : [id=5, name="walid", number="06123456789", address="Rue,Belfort" ]
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
        if (count(splittedWords[i], '"') == 1)
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
    if (ss.size() != 2)
        return false;
    m.insert({ss[0], ss[1]});
    return true;
}

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

// Expected : table SET (setters >= 1) WHERE (conditions >=1)
//            [table, SET, setter1, ',' , setter2,  WHERE, condition1, and/or, condition2,  ; ]
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
        throw(QueryErrorException("Syntaxe error : invalid query, one or more arguments are missing"));
    }

    int position = 0;

    // Check the table name
    if (position >= words.size() || includedIn(toUpper(words[position]), options))
        throw(QueryErrorException("missing table name"));

    sqlDetails.table = TableFile(words[position]);
    
    // Check SET
    if (position >= words.size() || toUpper(words[++position]) != set)
        throw(QueryErrorException("missing SET"));

    // Check Setters

    vector<string> setters;
    for (int i = ++position; i < words.size(); i++)
    {
        if (!includedIn(toUpper(words[i]), options))
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

    if (!validateSetters(setters, sqlDetails.setColumnsMapper))
        throw(QueryErrorException("error in setters syntax"));

    // Check WHERE
    if (position >= words.size() || toUpper(words[position]) != where)
        throw(QueryErrorException("missing where clause"));

    // Check conditions
    vector<string> conditions;
    for (int i = ++position; i < words.size(); i++)
    {
        // cout << "current word: " << words[i] << endl;
        if (!includedIn(toUpper(words[i]), options))
        {
            conditions.push_back(words[i]);
        }
        else
        {
            cout << "position: " << position << " i : " << i << endl;
            position = i;
            break;
        }
    }

    if (!validateConditions(conditions))
        throw(QueryErrorException("error in where conditions syntax"));

    // Check for the ';'
    if (position >= words.size() || count(words[position], ';') == 0)
        throw(QueryErrorException("error syntax : missing the ';' at the end of the query "));
}
UpdateQuery::UpdateQuery(std::string query, DbInfo db) : SqlQuery(db)
{   
    UpdateQuery::parse(query);
}

void UpdateQuery::check()
{
    this->sqlDetails.table.exist(this->db.getDbPath());
}
void UpdateQuery::execute() {

}
