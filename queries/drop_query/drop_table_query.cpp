#include "drop_table_query.h"

using namespace std;

DropTableQuery::DropTableQuery(std::string query, DbInfo db) : DropQuery(db)
{
    DropTableQuery::parse(query);
}

// Expected : table1 ;
// [table1 , ;] or [table1;]
void DropTableQuery::parse(string user_sql)
{
    sqlDetails.primaryCommand = "DROP TABLE";
    string end = ";";
    vector<string> words;
    istringstream iss(user_sql);
    do
    {
        string word;
        iss >> word;
        words.push_back(word);
    } while (iss);

    int position = 0;

    // Check the table name
    if (position >= words.size() || words[position] == end)
        throw(QueryErrorException("missing table name"));

    sqlDetails.tableDef = DefinitionFile(words[position], this->db.getDbPath());

    /// Check the ';'
    if (++position >= words.size() || (words[position] != end && count(words[position], ';') == 0))
        throw(QueryErrorException("error syntax : missing the ';' at the end of the query "));
}
void DropTableQuery::check()
{
    this->sqlDetails.tableDef.exist();
}

void DropTableQuery::execute() {
    this->sqlDetails.tableDef.deleteTableFile();
}