#include "sql_query.h"

// SqlQuery::SqlQuery(std::string _query, DbInfo _db, TableFile _table):query(_query), db(_db), table(_table){};

SqlQuery::SqlQuery(DbInfo _db): db(_db){};

SQLDETAILS SqlQuery::getSqlDetails(){
    return this->sqlDetails;
};


void SqlQuery::displayResults(vector<vector<string>> results, vector<field_record> queryFields){
    cout << "responses " <<endl;
    vector<int> minStar;
    int stringSize = 50;
    for (int i = 0 ; i < results[0].size() ; i++)
        minStar.push_back(stringSize);

    // get lowest star count for string formatting
    for(int i = 0 ; i < results.size() ; i++){
        for (int j = 0 ; j < results[i].size() ; j++){
            int starCount = count(results[i][j],'*');
            minStar[j] = starCount < minStar[j] ? starCount : minStar[j];
        }
    }
    
    // display response
    // header
    for( int i = 0 ; i < queryFields.size() ; i++ ) {
        int spaceNumber = stringSize - queryFields[i].field_name.size() - minStar[i];
        spaceNumber = spaceNumber < 0 ? 0 : spaceNumber;
        cout << " | " << queryFields[i].field_name << string(spaceNumber, ' ');    
    }
    cout << endl;
    // body (responses)
    for(int i = 0 ; i < results.size() ; i++){
        for (int j = 0 ; j < results[i].size() ; j++){
            string val = results[i][j];
            replace( val.begin(), val.end(), '*', ' ');
            val.resize(val.size() - minStar[j]);
            cout << " | " << val;    

        }
        cout << endl;
    }
    cout << endl;
};

// std::vector<SqlRow> SqlQuery::where(){};