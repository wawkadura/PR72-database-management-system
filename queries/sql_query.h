#ifndef SQL_QUERY_H
#define SQL_QUERY_H

#include <iostream>
#include <algorithm>
#include <sstream>

#include "../db_info.h"
#include "../table_file/table_file.cpp"
#include "../table_file/definition_file.cpp"
#include "sql_row.h"
#include "../utils.h"
#include <map>
#include <vector>

struct SQLDETAILS {   // Declare SQLDETAILS struct type
        std::string primaryCommand;  //
        // std::map<table, std::string> tabRecords;
        table_records tabRecords;
        TableFile table;
        DefinitionFile tableDef;
        std::map<std::string, std::string> setColumnsMapper;
        std::string conditions;
        std::string toString(){
            std::string str = "primary command:" + primaryCommand 
                + " \ntable:" + table.toString() 
                + " \nconditions:" + conditions
                + " \ncolumns:";
            for (field_record record : tabRecords.fields) {
                str = str + record.field_name + "\n";
            }
            return str;
        }
};

class SqlQuery {
private:
	// std::string query;
protected: 
    DbInfo db;
    SQLDETAILS sqlDetails;
public:


    SqlQuery(DbInfo _db);
    // SqlQuery(std::string _query, DbInfo _db, TableFile _table);
    virtual void parse(std::string user_sql)=0;
    virtual void check()=0;
    virtual void execute()=0;
    SQLDETAILS getSqlDetails();
    std::string parseToUpper(std::string text);
    // std::vector<SqlRow> where();
    // SQLDETAILS getSqlDetails();
    ~SqlQuery(){};
};

#endif