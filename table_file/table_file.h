#ifndef DEF_TABLE_FILE
#define DEF_TABLE_FILE
 
#include <iostream>
#include <string>

class Table_file
{
    public:
        Table_file();
        bool exist();
        void open();
        void close();
 
    private:
        std::string source_file();
        std::string query();
        
        
};
 
#endif