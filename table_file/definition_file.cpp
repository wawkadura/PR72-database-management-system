#include "table_file.h"
#include "definition_file.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

DefinitionFile::DefinitionFile(){};
DefinitionFile::DefinitionFile(string TableDef, string dbPath) : TableFile(TableDef, dbPath){};

table_definition DefinitionFile::get_table_definition()
{
    string lign;
    table_definition tableDef;

    string TableDefPath = this->dbPath + "/" + this->table + "/" + this->table + ".def";
    cout << TableDefPath << endl;
    ifstream file(TableDefPath);
    if (file.is_open())
    {
        // int field_count = 0;
        string field_name;
        string field_type;
        while (getline(file, lign))
        {
            istringstream ss(lign);
            ss >> field_name;
            ss >> field_type;
            tableDef.definitions.push_back({field_name, static_cast<field_types>(stoi(field_type))});
            // tableDef.definitions[field_count].field_type = static_cast<field_types>(stoi(field_type));
            // field_count++;
        }
        file.close();
    }
    else
        cout << "Table definition not opened";
    cout << "table def :" << tableDef.toString() << endl;
    return tableDef;
};

void DefinitionFile::write_table_definition(const table_definition &def)
{
    ofstream file;
    string str = "";
    for (field_definition d : def.definitions)
        str = str + to_string(static_cast<int>(d.field_type)) + " " + d.field_name + "\n";
    file.open(this->table);
    file << str;
    file.close();
};

void DefinitionFile::deleteTableFile()
{
    const char *c = this->table.c_str();
    DIR *const directory = opendir(c);
    if (directory)
    {
        struct dirent *entry;
        while ((entry = readdir(directory)))
        {
            if (!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name))
            {
                continue;
            }
            char filename[strlen(c) + strlen(entry->d_name) + 2];
            sprintf(filename, "%s/%s", this->table, entry->d_name);
            remove(filename);
        }
        closedir(directory);
        rmdir(c);
    }
}

void DefinitionFile::createFile()
{
    const char * directoryPath = ("db/"+ table).c_str();
    _mkdir(directoryPath);

    string name = "db/"+table+"/"+table+".def";;
    const char * filePath = name.c_str();
    std::ofstream{filePath};
}