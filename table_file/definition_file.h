#ifndef DEFINATION_FILE_H
#define DEFINITION_FILE_H

#include "Table_file.h"
#include "../utils.h"

class DefinitionFile : public TableFile
{   
    private: 
          
    public:
        DefinitionFile();
        table_definition get_table_definition(); 
        void write_table_definition(const table_definition &def);
};

#endif
