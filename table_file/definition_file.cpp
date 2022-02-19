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
    string TableDefPath = this->dbPath + "/" + this->table + "/" + this->table + ".def";

    ofstream file;
    string str = "";

    for (field_definition d : def.definitions)
    {
        str = str + d.field_name + " " + to_string(static_cast<int>(d.field_type)) + "\n";
    }

    file.open(TableDefPath);
    file << str;
    file.close();
};

void DefinitionFile::deleteTableFile()
{
    string TableDefPath = this->dbPath + "/" + this->table;

    const char *c = TableDefPath.c_str();
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
            char charz[100];
            strcpy(charz, TableDefPath.c_str());

            sprintf(filename, "%s/%s", charz ,entry->d_name);
            remove(filename);
        }
        closedir(directory);
        rmdir(c);
    }
    else
        cout << "je rentre pas dedans" << endl;
}

void DefinitionFile::createFile()
{
    const char *directoryPath = ("db/" + table).c_str();
    _mkdir(directoryPath);

    string name = "db/" + table + "/" + table + ".def";
    ;
    const char *filePath = name.c_str();
    std::ofstream{filePath};
}