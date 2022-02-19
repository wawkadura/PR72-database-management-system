#ifndef CONTENT_FILE_H
#define CONTENT_FILE_H

using namespace std;
#include <string>
#include <vector>
#include "table_file.h"

 
class ContentFile : public TableFile // the file class inherits the protected attribute from the parent class
{   
    private:
    
    public :
        ContentFile();
        ContentFile(std::string tableDef, std::string dbPath);
        vector<std::string> read_record(uint16_t length, uint32_t offset); 
        void write_record(const std::vector<std::string> &record, uint32_t offset);   
        void createFile();
        int size();
};

#endif
 