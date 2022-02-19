#include "table_file.h"
#include "key_file.h"
#include <fstream>
#include <direct.h>


KeyFile::KeyFile(){};

/*!
 * @brief function get_next_key extract the next key value from a table key file.
 * @return the next value of the key if it exists, 0 else
 */
uint64_t KeyFile::get_next_key(string table){
    const char *table_key =table.c_str();
    char rb[] = "rb";
    FILE *key = KeyFile::open_key_file(table_key, rb);
        if (key){
            uint64_t key_value;
            fread(&key_value, sizeof(uint64_t), 1, key);
            fclose(key);
            return key_value;
            delete key;
        }
        return 0;
};

/*!
 * @brief function update_key updates the key value in the key file. Key value is updated if and only if the new value
 * if higher than the stored value. The value sent to the function is the last value inserted into the table, so the
 * function must increment it before comparing to the key file content.
 */
void KeyFile::update_key(string table,uint64_t last_value){
    ++last_value;
    const char *table_key =(this->table).c_str();
    uint64_t file_value = get_next_key(table_key);
    char wb[] = "wb";

    FILE *key = KeyFile::open_key_file(table_key, wb);
    fwrite(file_value > last_value ? &file_value : &last_value, sizeof(unsigned long long), 1, key);
    fclose(key);
    
    // KeyFile::close();
};

FILE* KeyFile::open_key_file(const char *table_key,char *mode){
    FILE *file = fopen(table_key, mode);
    if (file){
        return file;
        delete file;
    }
    return NULL;
};

void KeyFile::createFile()
{
    const char * directoryPath = ("db/"+ table).c_str();
    _mkdir(directoryPath);

    string name = "db/"+table+"/"+table+".key";;
    const char * filePath = name.c_str();
    std::ofstream{filePath};
}