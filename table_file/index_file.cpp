#include <iostream>
#include <fstream>
#include <string>
#include "table_file.h"
#include "index_file.h"
 #include <direct.h>

IndexFile::IndexFile(){};
IndexFile::IndexFile(string TableDef, string dbPath): TableFile(TableDef, dbPath){};

void IndexFile::write_index_entry(const index_entry &entry, uint32_t offset){};
index_entry IndexFile::get_index_entry(uint32_t position){return index_entry();};

map<int, int> IndexFile::getOffsets(bool active){
    map<int, int> offsets;
    string tablePath = this->dbPath + "/" + this->table+"/"+this->table+".idx";
    // cout << tablePath << " : it is my path > content file";

    string activeStr = active ? "1":"0";
    string lign;
    ifstream file(tablePath);
    if (file.is_open()) {
        // int field_count = 0;
        string activ;
        string offset;
        string length;
        while (getline(file, lign)) {
            istringstream ss(lign);
            ss >> activ;
            ss >> offset;
            ss >> length;
            if (activ == activeStr)
                offsets.insert({stoi(offset),stoi(length)});
        }
        file.close();
    }
    // cout << "index offsets" << endl;
    // for(pair<int,int> i : activeOffsets){
    //     cout << i.first << ", " << i.second << endl;
    // }
    return offsets;
}

void IndexFile::createFile()
{
    const char * directoryPath = ("db/"+ table).c_str();
    _mkdir(directoryPath);

    string name = "db/"+table+"/"+table+".idx";;
    const char * filePath = name.c_str();
    std::ofstream{filePath};
}

int IndexFile::size() {
    string tablePath = this->dbPath + "/" + this->table+"/"+this->table+".idx";
    std::fstream  in(tablePath, std::ios_base::in | std::ios_base::ate | std::ios_base::binary);
    in.seekg(0, ios::end);
    int size = in.tellg();
    return size; 
}