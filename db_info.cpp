#include "db_info.h"
using namespace std;

DbInfo::DbInfo(string path):current_db_path(path){}

void DbInfo::setDbPath(string path){
    DbInfo::current_db_path = path;
}

std::string DbInfo::getDbPath(){
    return DbInfo::current_db_path;
}
