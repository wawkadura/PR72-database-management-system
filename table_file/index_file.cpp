#ifndef DEF_INDEX_FILE
#define DEF_INDEX_FILE
 
#include <iostream>
#include <string>
#include "table_file.h"
 
class Index_file : public TableFile
{
    private:
        bool is_active;
        uint32_t position ;
        uint16_t length;
    public:
        void write_index_entry(const index_entry &entry, uint32_t offset);
        index_entry get_index_entry(uint32_t position);
};
 
#endif