#include "table_file.h"
 
#include <iostream>
#include <string>
#include "table_file.h"
 
class KeyFile : public TableFile
{
    public:
        uint64_t get_next_key();
        void update_key(uint64_t last_value);
};
 
#endif