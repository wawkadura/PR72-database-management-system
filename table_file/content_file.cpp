#ifndef DEF_CONTENT_FILE
#define DEF_CONTENT_FILE

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include "table_file.h"
#include <fstream>
 
class Content_file : public Table_file
{   
    public :
        std::vector<uint8_t> read_record(uint16_t length, uint32_t offset); 
        void write_record(const std::vector<uint8_t> &record, uint32_t offset);   
};

//note done
std::vector<uint8_t> Content_file::read_record(uint16_t length, uint32_t offset){
    ofstream ofstr("test.txt", std::ofstream::binary);
    string line;
    ofstr.seekp(offset, ios::beg); // set the possition of the pointeur
    ofstr >> line; //read line in the file
    return line.length();
}
//note done
void Content_file::write_record(const std::vector<uint8_t> &record, uint32_t offset){

    ofstream ofstr("test.txt", std::ofstream::binary);
    for (int i = 0; i < offset; i++){
        ofstr.seekp('\n', std::ios_base::cur); // set the possition of the pointeur
    };
    ofstr<<record; //write line in the file
}


#endif