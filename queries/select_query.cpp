#include "select_query.h"
#include "../error/query_error_exception.h"

using namespace std;

SelectQuery::SelectQuery(std::string query, DbInfo db):SqlQuery(db){
    SelectQuery::parse(query);
}


std::string SqlQuery::parseToUpper(std::string text){
    std::transform(
        text.begin(), 
        text.end(), 
        text.begin(),
        [](unsigned char c)
        { return std::toupper(c); }
    );
    return text;
};

void SelectQuery::parse(string user_sql) {
    std::cout << "parse SELECT : SELECT " << user_sql << endl;
    sqlDetails.primaryCommand = "SELECT";

    string upperCaseSQL = SqlQuery::parseToUpper(user_sql);

    int fromIndex = upperCaseSQL.find("FROM");
    if (fromIndex==std::string::npos) {
        cout << "Mauvaise requete" << endl;
        throw(QueryErrorException("Missing FROM"));
    }

    string columns = user_sql.substr(0, fromIndex-1);
    // remove spaces
    string::iterator end_pos = remove(columns.begin(), columns.end(), ' ');
    columns.erase(end_pos, columns.end());

    // split columns by , loop in and push_back in map
    table_records tabRecords;
    stringstream ss(columns);
    string col;
    while (getline(ss, col, ',')) {
        // field_values a = {0,0,0,col};
        // field_record b = {col,field_types(4),a};
        tabRecords.fields.push_back({col,field_types(4),{0,0,0,col}});
    }
    sqlDetails.tabRecords = tabRecords;

    // get table name
    int fromEndIndex = fromIndex + 5;
    int spaceAfterTableIndex = user_sql.find(' ',fromEndIndex);
    string tableName = user_sql.substr(fromEndIndex, spaceAfterTableIndex-fromEndIndex);
    sqlDetails.table = TableFile(tableName, db.getDbPath());
    sqlDetails.tableDef = DefinitionFile(tableName, db.getDbPath());
    sqlDetails.contentFile = ContentFile(tableName, db.getDbPath());
    sqlDetails.indexFile = IndexFile(tableName, db.getDbPath());

    // get conditions
    int whereIndex = upperCaseSQL.find("WHERE");
    if (whereIndex!=std::string::npos) {
        sqlDetails.conditions = user_sql.substr(whereIndex+6);
    }


    cout << "---------------" << endl << sqlDetails.toString() << endl << "---------------" << endl;
    cout << "END parse SELECT" << endl;
}


void SelectQuery::check() {
    this->sqlDetails.toString();
    this->sqlDetails.table.exist();
    vector<field_record> queryFields = this->sqlDetails.tabRecords.fields;

    if(queryFields.size()==1 && queryFields[0].field_name=="*") {
        expand();
        return;
    }
    bool check = checkFields(
        this->sqlDetails.tabRecords, 
        this->sqlDetails.tableDef.get_table_definition()
    );
    if (check == false) {
    	cout << "Fields not corresponding!" << endl;
        throw(QueryErrorException("Fields not corresponding!"));
    }
    else
        cout << "Fields corresponding!" << endl;

}

void SelectQuery::expand(){
    vector<field_record> queryFields = this->sqlDetails.tabRecords.fields;
    if(queryFields.size()==1 && queryFields[0].field_name=="*"){
        queryFields.clear();
        for (field_definition f : this->sqlDetails.tableDef.get_table_definition().definitions)
            queryFields.push_back({f.field_name, f.field_type, {0,0,0,f.field_name}});
    }
    this->sqlDetails.tabRecords.fields = queryFields;
    cout << "eazezae";
    cout << this->sqlDetails.tableDef.toString() << endl;
}


void SelectQuery::execute(){
    map<int, int> activeOffsets = this->sqlDetails.indexFile.getOffsets(true); // first : Offset, second : Length
    vector<field_definition> tableFields = this->sqlDetails.tableDef.get_table_definition().definitions;
    vector<field_record> queryFields = this->sqlDetails.tabRecords.fields;
    map<string,string> map;
    std::map<string,string>::iterator itr;
    vector<vector<string>> resultsTable;

    for( field_definition def : tableFields )
        map.insert({def.field_name, ""});
    

    int resultIndex = 0;

    for(pair<int,int> i : activeOffsets){
        vector<string> dataFields = this->sqlDetails.contentFile.read_record(i.second, i.first);

        int idx = 0;
        for( itr = map.begin(); itr != map.end(); itr++ ) {
            itr->second = dataFields[idx];
            idx++;
        }
        // add one dimension 
        resultsTable.push_back({});
        for( field_record rec : queryFields ) {
            resultsTable[resultIndex].push_back(map.find(rec.field_name)->second);
        }
        resultIndex++;
    }
    displayResults(resultsTable, queryFields);

}
