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
        std::string dbPath;
    public:
        TableFile();
        TableFile(std::string _table, std::string _dbPath);
        std::string toString();
        std::string getDbPath();
        void exist();
        ofstream open();
        void close();
};
 
#endif