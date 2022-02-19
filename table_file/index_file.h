#include <iostream>
#include <string>
#include "table_file.h"
#include "../utils.h"
 
class IndexFile : public TableFile
{
    private:
        bool is_active;
        uint32_t position ;
        uint16_t length;

    public:
        IndexFile();
        IndexFile(std::string tableDef, std::string dbPath);
        void write_index_entry(const index_entry &entry, uint32_t offset, int colNum);
        index_entry get_index_entry(uint32_t position);
        map<int,int> getOffsets(bool active);
        void delete_record();
        void createFile();
        int size();
};

