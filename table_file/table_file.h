#ifndef TABLE_FILE_H
#define TABLE_FILE_H
 
#include <iostream>
#include <string>

class TableFile
{
    public:
        TableFile();
        bool exist();
        void open();
        void close();
 
    private:
        std::string source_file;
        std::string query();
        
        
};
 
#endif