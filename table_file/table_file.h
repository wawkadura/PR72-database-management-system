#ifndef TABLE_FILE_H
#define TABLE_FILE_H
 
#include <iostream>
#include <string>
#include "../utils.h"
using namespace std;

class TableFile
{
    protected:
        std::string table;
    public:
        TableFile();
        TableFile(std::string _table);
        std::string toString();
        void exist();
        ofstream open();
        void close();
      
};
 
#endif