using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../error/query_error_exception.h"
#include "content_file.h"
#include "table_file.h"
#include <direct.h>


ContentFile::ContentFile(){};
ContentFile::ContentFile(string TableDef, string dbPath): TableFile(TableDef, dbPath){};

vector<string> ContentFile::read_record(uint16_t length, uint32_t offset){
    string tablePath = this->dbPath + "/" + this->table+"/"+this->table+".data";
    // cout << tablePath << " : it is my path > content file";

    ifstream file(tablePath);
    char line[500]  = "";

    file.seekg(offset); // set the position of the pointeur
    file.read(line, length); // read line in the file 
    // cout << line << endl;
    return Split(string(line),'|');
};

void ContentFile::write_record(const vector<std::string> &record, uint32_t offset){
    ofstream file(this->table+"/"+this->table+".data");
    file.seekp(offset, ios::end); // set the possition of the pointeur to the end of the file
    for (int i=0; i < record.size(); i++){
        file<<record[i]<<endl; //write lines in the file
    }; 
    ContentFile::close();
};


void ContentFile::createFile()
{
    const char * directoryPath = ("db/"+ table).c_str();
    _mkdir(directoryPath);

    string name = "db/"+table+"/"+table+".data";;
    const char * filePath = name.c_str();
    std::ofstream{filePath};
}

int ContentFile::size() {
    std::fstream  in(this->table+"/"+this->table+".data", std::ios_base::in | std::ios_base::ate | std::ios_base::binary);
    in.seekg(0, ios::end);
    int size = in.tellg();
    return size; 
}