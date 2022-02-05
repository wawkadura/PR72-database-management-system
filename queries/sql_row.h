#ifndef SQL_ROW_H
#define SQL_ROW_H

#include <iostream>

class SqlRow {
private:
	std::string query;
public:
    SqlRow();
    ~SqlRow(){};
};

#endif