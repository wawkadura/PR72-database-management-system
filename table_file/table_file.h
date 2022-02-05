#ifndef TABLE_FILE_H
#define TABLE_FILE_H
 
#include <iostream>
#include <string>

class TableFile
{
    private:
        std::string table; 
    public:
        TableFile(std::string _table);
        bool exist();
        void open();
        void close();
          
};
 
#endif