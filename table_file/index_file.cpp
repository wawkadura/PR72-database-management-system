#include <iostream>
#include <string>
#include "table_file.h"
#include "index_file.h"
 
IndexFile::IndexFile(){};
void IndexFile::write_index_entry(const index_entry &entry, uint32_t offset){};
index_entry IndexFile::get_index_entry(uint32_t position){};