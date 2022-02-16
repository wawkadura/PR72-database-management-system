#ifndef SQL_ROW_H
#define SQL_ROW_H

#include <iostream>

class SqlRow {
protected:
	std::string query;
public:
    SqlRow();
    ~SqlRow(){};
};

#endif