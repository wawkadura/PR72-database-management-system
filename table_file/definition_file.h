#ifndef DEFINATION_FILE_H
#define DEFINITION_FILE_H

#include "Table_file.h"
 
class DefinitionFile : public TableFile
{   
    private: 
          
    public:
        DefinitionFile();
        table_definition get_table_definition(); 
        void write_table_definition(const table_definition &def);
};

// enum field_type_t  {string, int, bool};
#endif
