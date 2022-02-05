#ifndef DEF_KEY_FILE
#define DEF_KEY_FILE
#include "table_file.h"
 
#include <iostream>
#include <string>
#include "table_file.h"
 
class Key_file : public Table_file
{
    public:
        uint64_t get_next_key();
        void update_key(uint64_t last_value);
};
 
#endif