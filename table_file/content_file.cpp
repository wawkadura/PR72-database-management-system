#ifndef DEF_CONTENT_FILE
#define DEF_CONTENT_FILE

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include "table_file.h"
#include <fstream>
#include "error/query_error_exception.h"
 
class ContentFile : public TableFile // the file class inherits the protected attribute from the parent class
{   
    public :
        ContentFile();
        vector<string> read_record(uint16_t length, uint32_t offset); 
        void write_record(const std::vector<uint8_t> &record, uint32_t offset);   
};

vector<string> ContentFile::read_record(uint16_t length, uint32_t offset){
    ifstream file(this->table);
    string line;
    vector<string> mylines;
    
    file.seekg(offset*length, ios::beg); // set the possition of the pointeur
    while (getline(file, line)) //read lines in the file 
    {   
        mylines.push_back(line);
        return mylines;
    };
}

void ContentFile::write_record(const vector<uint8_t> &record, uint32_t offset){

    ifstream file(this->table);
    file.seekg('\n', ios::end); // set the possition of the pointeur
    for (string i = 0; i < record.size(); i++){
        file<<i; //write line in the file
    };
    
}


#endif