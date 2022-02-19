#include "create_table_query.h"
#include "../../utils.h"

using namespace std;

CreateTableQuery::CreateTableQuery(std::string query, DbInfo db) : SqlQuery(db)
{
    CreateTableQuery::parse(query);
}
void CreateTableQuery::check() {}

bool validateAttributs(vector<string> attributs, map<string, string> &m)
{
    string first = attributs[0];
    string last = attributs[attributs.size() - 1];
    if (count(first, '(') != 1 || count(last, ')') != 1)
        return false;
    string att = "";
    string _type = "";

    for (int i = 0; i < attributs.size(); i++)
    {
        string word = attributs[i];
        if (word == "(" || word == ")")
            continue;
        if (word == ";")
            break;
        if (i == 0)
            word = removeChar(word, '(');
        if (i == attributs.size() - 1)
            word = removeChar(word, ')');
        word = removeChar(word, ',');
        if (word == "")
            break;
        if (toUpper(word) == "KEY")
            continue;
        if (att != "")
        {
            m.insert({att, word});

            att = "";
        }
        else
        {
            att = word;
        }
    }
    for (auto var : m)
    {
        cout << var.first << endl;
        cout << var.second << endl;
    }

    if (m.size() == 0)
        return false;

    return true;
}

table_definition mapToDefinition(map<string, string> m)
{
    table_definition definitions;
    map<string, string>::iterator it;
    std::vector<field_definition> fields;

    for (it = m.begin(); it != m.end(); it++)
    {
        // TODO: replace it by a switch of different types
        field_definition fd = {field_name : it->first, field_type : TYPE_TEXT};
        fields.push_back(fd);
    }

    return definitions;
}

void CreateTableQuery::parse(string user_sql)
{
    sqlDetails.primaryCommand = "CREATE TABLE";
    string end = ";";
    vector<string> words;

    istringstream iss(user_sql);
    do
    {
        string word;
        iss >> word;
        if (word != "")
            words.push_back(word);

    } while (iss);

    int position = 0;

    // Check the table name
    if (position >= words.size() || words[position] == end)
        throw(QueryErrorException("missing table name"));

    sqlDetails.tableDef = DefinitionFile(words[position], this->db.getDbPath());

    // Check attributs
    vector<string> attributs;
    // cout << words.size() << endl;
    for (int i = ++position; i < words.size(); i++)
    {
        if (words[i] != end && words[i] != "")
        {
            attributs.push_back(words[i]);
            position = i;
        }
        else
        {
            position = i;
            break;
        }
    }

    // for(auto var : attributs)
    // {
    //     cout<< var << endl;
    // }

    if (attributs.size() < 1)
        throw(QueryErrorException("missing attributs"));

    map<string, string> setColumnsMapper;

    if (!validateAttributs(attributs, setColumnsMapper))
        throw(QueryErrorException("error in attributs syntax"));

    this->tb = mapToDefinition(setColumnsMapper);

    // Check the ';'
    // cout << words[position] << endl;
    cout << words[position] << endl;
    if (position >= words.size() || (words[position] != end && count(words[position], ';') == 0))
        throw(QueryErrorException("error syntax : missing the ';' at the end of the query "));
}

void CreateTableQuery::execute()
{
    this->sqlDetails.tableDef.createFile();
    this->sqlDetails.tableDef.write_table_definition(this->tb);
    this->sqlDetails.contentFile = ContentFile(this->sqlDetails.tableDef.toString(), this->sqlDetails.tableDef.getDbPath());
    this->sqlDetails.indexFile = IndexFile(this->sqlDetails.tableDef.toString(), this->sqlDetails.tableDef.getDbPath());
}