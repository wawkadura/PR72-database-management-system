#ifndef DEF_DEFINITION_FILE
#define DEF_DEFINITION_FILE
 
#include <iostream>
#include <string>
#include "Table_file.h"
 
class Definition_file : public Table_file
{
    public:
        table_definition get_table_definition(); 
        void write_table_definition(const table_definition &def);
};
 
#endif