#include "update_query.h"
#include <sstream>
#include <string>
#include "error/query_error_exception.h"

using namespace std;

UpdateQuery::UpdateQuery(std::string query, DbInfo db) : SqlQuery::SqlQuery(db)
{
    UpdateQuery::parse(query);
}

// table SET (setters >= 1) WHERE (conditions >=1)
// ['table', 'SET', 'setvariable', ',' ,'setValue',  'and/or/WHERE', setter2/condition1, ';' ]
void UpdateQuery::parse(string user_sql)
{
    SQLDETAILS details;
    details.primaryCommand = "UPDATE";
    string set = "SET";
    string where = "WHERE";
    string end = ";";

    string words[user_sql.length()];
    istringstream iss(user_sql);
    do
    {
        string word;
        iss >> word;
        words->append(word);
    } while (iss);

    // Check SET
    int position = 0;
    if (parseToUpper(words[++position]) != set)
        throw(QueryErrorException("missing SET"));

    // Check Setters
    string setters[user_sql.length()];
    for (int = ++position; i < words.size(); i++)
    {
        if (notIncludedIn(parseToUpper(words[i])))
        {
            setters->append(words[i]);
        }
        else
        {
            position = i;
            break;
        }
    }

    if (setters.size() < 1)
        throw(QueryErrorException("missing setters"));

    if (!validateSetters(setters))
        throw(QueryErrorException("error in setters syntax"));

    // Check WHERE

    if (parseToUpper(words[position]) != where)
        throw(QueryErrorException("missing where clause"));
    // Check conditions
    string conditions[user_sql.length()];
    // get conditions list 
    if (!validateConditions(conditions))
        throw(QueryErrorException("error in setters syntax"));

    if()
}

bool notIncludedIn(string s, string ss[], int size)
{
    for (int i = 0; i < size; i++)
        if (s == ss[i])
            return true;

    return false;
}

// TODO: implimente body
bool validateSetters(string setters[])
{
    return false;
}

// TODO: implimente body
bool validateConditions(string setters[])
{
    return false;
}

void UpdateQuery::check() {}
void UpdateQuery::execute() {}
