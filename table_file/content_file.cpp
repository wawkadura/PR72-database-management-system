using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "error/query_error_exception.h"
#include "content_file.h"
#include "table_file.h"

ContentFile::ContentFile(){};

vector<string> ContentFile::read_record(uint16_t length, uint32_t offset){
    ifstream file(this->table+"/"+this->table+".data");
    string line;
    vector<string> myline;
    file.seekg(offset*length, ios::beg); // set the possition of the pointeur
    getline(file, line); //read line in the file 
    myline.push_back(line);
    return myline;
};

void ContentFile::write_record(const vector<uint8_t> &record, uint32_t offset){
    ofstream file(this->table+"/"+this->table+".data");
    file.seekp(offset, ios::end); // set the possition of the pointeur to the end of the file
    for (int i=0; i < record.size(); i++){
        file<<record[i]<<endl; //write lines in the file
    }; 
    ContentFile::close();
};


 