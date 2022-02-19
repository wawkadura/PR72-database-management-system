#include <fstream>
#include <direct.h>
#include <iostream>

using namespace std;
int main(){
    std::string table = "toto";

    const char * directoryPath = ("db/"+ table).c_str();
    _mkdir(directoryPath);

    std::cout << directoryPath<< std::endl;
    string name = "db/"+table+"/"+table+".data";;

    const char * filePath = name.c_str();
    std::cout << filePath<< std::endl;

    std::ofstream{filePath};
    return 0;
}