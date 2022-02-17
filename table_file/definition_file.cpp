#include "table_file.h"
#include "definition_file.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

DefinitionFile::DefinitionFile(){};
DefinitionFile::DefinitionFile(string TableDef): TableFile(TableDef){};

table_definition DefinitionFile::get_table_definition(string dbPath){
    string lign;
    table_definition tableDef;

    string TableDefPath =  dbPath + "/" + this->table + "/" + this->table + ".def";
    cout << TableDefPath << endl;
    ifstream file(TableDefPath);
    if (file.is_open()) {
        // int field_count = 0;
        string field_name;
        string field_type;
        while (getline(file, lign)) {
            istringstream ss(lign);
            ss >> field_name;
            ss >> field_type;
            tableDef.definitions.push_back({field_name, static_cast<field_types>(stoi(field_type))});
            // tableDef.definitions[field_count].field_type = static_cast<field_types>(stoi(field_type));
            // field_count++;
        }
        file.close();
    }
    else
        cout << "Table definition not opened";
    cout << "table def :" << tableDef.toString() << endl;
    return tableDef;
}; 

void DefinitionFile::write_table_definition(const table_definition &def){
    ofstream file;
    string str = "";
    for ( field_definition d : def.definitions )
        str = str + to_string(static_cast<int>(d.field_type)) + " " + d.field_name + "\n";
    file.open(this->table);
    file << str;
    file.close();
};

 
