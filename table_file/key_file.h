#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "table_file.h"
using namespace std;

class KeyFile : public TableFile
{
    private: 
        FILE *open_key_file(const char *table_key,char *mode);
    public:
        KeyFile();
        uint64_t get_next_key(std::string table);
        void update_key(string table,uint64_t last_value);
};
 
#endif