#ifndef DB_INFO_H
#define DB_INFO_H
#include <vector>

class DbInfo {
private:
    std::string current_db_path;
public:
    DbInfo(std::string m);
    std::vector<std::string> getTables();
    std::string getDbPath();
    void setDbPath(std::string path);
};

#endif