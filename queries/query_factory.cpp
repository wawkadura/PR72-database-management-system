#include <iostream>
#include "query_factory.h"

using namespace std;

// Command resolveCommand (std::string input) {
//     if( input == "SELECT" ) return SELECT;
//     if( input == "CREATE" ) return CREATE;
//     if( input == "INSERT" ) return INSERT;
//     if( input == "UPDATE" ) return UPDATE;
//     if( input == "DELETE" ) return DELETE;
//     if( input == "DROP" ) return DROP;
//     return INVALID;
// }

Command QueryFactory::resolveCommand(std::string input)
{
    static const std::map<std::string, Command> commandStrings{
        {"SELECT", SELECT},
        {"CREATE", CREATE},
        {"INSERT", INSERT},
        {"UPDATE", UPDATE},
        {"DELETE", DELETE},
        {"DROP", DROP}};

    auto itr = commandStrings.find(input);
    if (itr != commandStrings.end())
    {
        return itr->second;
    }
    return INVALID;
}

static SqlQuery *QueryFactory::generate_query(std::string sql, DbInfo db)
{
    SqlQuery *query = NULL;

    std::string command = sql.substr(0, sql.find(" "));
    // parse to upper case
    std::transform(command.begin(), command.end(), command.begin(),
                   [](unsigned char c)
                   { return std::toupper(c); });

    switch (resolveCommand(command))
    {
    case SELECT:
        query = new SelectQuery(sql, db);
        break;
    case CREATE:
        query = new CreateQuery(sql, db);
        break;
    case INSERT:
        query = new InsertQuery(sql, db);
        break;
    case UPDATE:
        query = new UpdateQuery(sql, db);
        break;
    case DELETE:
        query = new DeleteQuery(sql, db);
        break;
    case DROP:
        query = new DropQuery(sql, db);
        break;
    }
    return query;
}