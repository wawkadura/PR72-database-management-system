#ifndef TABLE_FILE_H
#define TABLE_FILE_H
 
#include <iostream>
#include <string>

class TableFile
{
    protected:
        std::string table; 
    public:
        TableFile(std::string _table);
        void exist();
        void open();
        void close();
      
};
 
#endif