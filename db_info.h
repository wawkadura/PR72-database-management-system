#ifndef DB_INFO_H
#define DB_INFO_H

class DbInfo {
private:
    std::string current_db_path;
public:
    DbInfo(std::string m);
    std::string getDbPath();
    void setDbPath(std::string path);
};

#endif