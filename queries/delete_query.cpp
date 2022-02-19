#include "delete_query.h"

using namespace std;

DeleteQuery::DeleteQuery(std::string query, DbInfo db):SqlQuery( db){
    DeleteQuery::parse(query);
}
void DeleteQuery::parse(string user_sql) {
    sqlDetails.primaryCommand = "DELETE";
    string end = ";";
    string from = "FROM";
    vector<string> words;
    istringstream iss(user_sql);
    do
    {
        string word;
        iss >> word;
        words.push_back(word);
    } while (iss);

    int position = 0;
        // Check From
    if (position >= words.size() || toUpper(words[position]) != from)
        throw(QueryErrorException("missing From"));

    // Check the table name
    if (++position >= words.size() || words[position] == end)
        throw(QueryErrorException("missing table name"));
    string name = removeChar(words[position], ';');
    cout << "TABLE : "<< name <<endl;

    sqlDetails.tableDef = DefinitionFile(name, this->db.getDbPath());

    /// Check the ';'
        cout << "end : "<< words[position] <<endl;

    if (++position >= words.size() || (words[position] != end && count(words[position], ';') == 0))
        throw(QueryErrorException("error syntax : missing the ';' at the end of the query "));
}

void DeleteQuery::check() {
    this->sqlDetails.tableDef.exist();
}

void DeleteQuery::execute(){
    this->sqlDetails.indexFile = IndexFile(this->sqlDetails.tableDef.toString(), this->sqlDetails.tableDef.getDbPath());
    this->sqlDetails.indexFile.delete_record();
}
