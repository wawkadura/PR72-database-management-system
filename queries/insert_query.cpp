#include "insert_query.h"
#include <vector>
#include<algorithm>

using namespace std;

InsertQuery::InsertQuery(string query, DbInfo db):SqlQuery(db){
    InsertQuery::parse(query);
}

//insert into table_name values('toto','prenom');
// [into, values( )]
string checkFirststring(string words){
    string str;
    str = words.substr(0,6);
    return str;
};
void getPaseValues(vector <string> words,int position){
    //insert into table values ('toto','toto');
        // Check  ()
        ++position;
        int openP=words[position].find("(");
        int closinP=words[position].find(")");
        if (openP==std::string::npos || closinP==std::string::npos) {
            throw(QueryErrorException("missing closing condition ()")); 
        }
        //check end of the querry
        if(!words[position].find(";")){
            throw(QueryErrorException("missing '; in the of the query")); 
        };
        //check cotnet inside ()
        if (words[position].length() < 3)
            throw(QueryErrorException("missing values inside parenthesis"));
        //('toto','toto'); : i want to remove () and ;
        words[position].erase(remove(words[position].begin(), words[position].end(), '('), words[position].end());
        words[position].erase(remove(words[position].begin(), words[position].end(), ')'), words[position].end());
        words[position].erase(remove(words[position].begin(), words[position].end(), ';'), words[position].end());

        vector<string> myValues = Split(words[position], ',');  
         for (string i : myValues) {
            cout<<i<<endl;
            // sqlDetails.tabRecords = mapToRecords(setColumnsMapper);  
        }  
}

void InsertQuery::parse(string user_sql){
    sqlDetails.primaryCommand = "INSERT";
    string into = "INTO";
    string values = "VALUES";
    string end = ";";
    vector<string> options = {into, values, end};
    vector<string> words;
    istringstream iss(user_sql);

    do
    {
        string word;
        iss >> word;
        words.push_back(word);
    } while (iss);

    // Check the minimum requirement of words
    if (words.size() < 3)
    {
        throw(QueryErrorException("Syntaxe error : invalid query, one or more arguments are missing"));
    }

    int position = 0;

    // Check into condition
    ++position;
    if (position >= words.size() || toUpper(words[position]) != into)
        throw(QueryErrorException("missing condition INTO"));

    sqlDetails.tableDef = DefinitionFile(words[++position], this->db.getDbPath()); //get the table name 
 
    //if the position 3 is values 
    if(words[++position].size()!=6 && toUpper(checkFirststring(words[position]))==values){
        // what i will get :insert into table values ('toto',toto');
        //check the next character
        if (words[position].substr(6,1)!= "("){
            throw(QueryErrorException("missing condition '('"));
        }else{
            for (int i = 0; i < words.size(); i++)
            {
                if (words[i+1] == "(")
                {
                    i++;
                    words[position].insert(i, " ");
                }
            }
            //values ('toto',toto');
            //last step is to get value
            getPaseValues(words,position);
        }   
    }else if(position >= words.size() || toUpper(words[position]) != values)
    {
        throw(QueryErrorException("missing condition VALUES")); 
    }else{
        //('toto',toto');
        getPaseValues(words,position);
    }
        
};

void InsertQuery::check() {
    this->sqlDetails.tableDef.exist();
    bool check = checkFields(
        this->sqlDetails.tabRecords,
        this->sqlDetails.tableDef.get_table_definition());
    if (check == false)
    {
        throw(QueryErrorException("Fields not corresponding!"));
    }
}

void InsertQuery::execute() {

}
