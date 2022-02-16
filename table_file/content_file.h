#ifndef CONTENT_FILE_H
#define CONTENT_FILE_H

using namespace std;
#include <string>
#include <vector>
#include "table_file.h"

 
class ContentFile : public TableFile // the file class inherits the protected attribute from the parent class
{   
    public :
        ContentFile();
        vector<std::string> read_record(uint16_t length, uint32_t offset); 
        void write_record(const std::vector<uint8_t> &record, uint32_t offset);   
};

#endif
 