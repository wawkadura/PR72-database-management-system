#include "insert_query.h"
#include "../table_file/key_file.h"
#include <vector>
#include "../utils.h"
#include "../error/query_error_exception.cpp"

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

    cout<<words[position];
    sqlDetails.tableDef = DefinitionFile(words[++position], this->db.getDbPath()); //get the table name 
    cout<<words[position];
    // //if the position 3 is values 
    // if(words[++position].size()!=6 && toUpper(checkFirststring(words[position]))==values){
    //     // what i will get :insert into table values ('toto',toto');
    //     //check the next character
    //     if (words[position].substr(6,1)!= "("){
    //         throw(QueryErrorException("missing condition '('"));
    //     }else{
    //         for (int i = 0; i < words.size(); i++)
    //         {
    //             if (words[i+1] == "(")
    //             {
    //                 i++;
    //                 words[position].insert(i, " ");
    //             }
    //         }
    //         //values ('toto',toto');
    //         //last step is to get value
    //         cout <<"Not done"<< words[position] << std::endl;
    //     }   
    // }else if(position >= words.size() || toUpper(words[position]) != values)
    // {
    //     throw(QueryErrorException("missing condition VALUES")); 
    // }else{

    //     //insert into table values ('toto','toto');
    //     // Check values inside ()
    //     vector<string> vals;
    //     for (int i = ++position; i < words.size(); i++)
    //     {
    //         if (!includedIn(toUpper(words[i]), options))
    //         {
    //             vals.push_back(words[i]);
    //         }
    //         else
    //         {
    //             position = i;
    //             break;
    //         }
    //     }
    //     if (vals.size() < 1)
    //     throw(QueryErrorException("missing values inside parenthesis"));

    //     //check last caractère == ;
    //     if (words.back()!=end){
    //        throw(QueryErrorException("missing the isert sould end with ';'")); 
    //     }

    //     //('toto','toto'); : i want to remove () and ;
    //     removeChar(words[position], ')');
    //     removeChar(words[position], '(');
    //     removeChar(words[position], ';');

    //     //'toto','toto'
    //     vector<string> myValues = Split(words[position], ',');  

    //      for (string i : myValues) {
            
    //         cout<<i<<endl;
    //         // sqlDetails.tabRecords = mapToRecords(setColumnsMapper);  
    //     }  
    // }
        
};

void InsertQuery::check() {}

void InsertQuery::execute() {}
