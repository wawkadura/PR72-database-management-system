#include "db_info.h"
using namespace std;

DbInfo::DbInfo(string path):current_db_path(path){}

DbInfo::setDbPath(string path){
    DbInfo::this.current_db_path = path;
}

DbInfo::getDbPath(){
    return QueryError::this.current_db_path;
}
