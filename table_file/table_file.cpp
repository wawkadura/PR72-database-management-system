using namespace std;
#include <sys/stat.h>
#include <iostream> 
#include <fstream> 
#include "table_file.h"
#include "../error/query_error_exception.h"

TableFile::TableFile(): table(""){};
TableFile::TableFile(std::string _table): table(_table){};

void TableFile::exist(std::string dbPath){
    std::string tablePath = dbPath + "/" + table;
    struct stat buffer;
    // TODO: add the database instead of db
    string path = "db/"+table+"/"+table+".def";
    
    //check if directory exit
    if (stat(tablePath.c_str(), &buffer) != 0) {
    	cout << "Directory " << table << " doesn't exist!" << endl;
        throw(QueryErrorException("Directory doesn't exist!"));
    } else {
    	cout << "Directory " << table << " exists!" << endl;
    }
};   

void TableFile::close(){
    ofstream file;  
    file.open (table);  
    if(file.is_open()){  
        file.close();//file close  
        cout<<"File close successfully."<<endl;  
    }  
    else{  
        cout<<"Error in file opening"<<endl;  
    }  
};

ofstream TableFile::open(){
    ofstream file;  
    ofstream empty;
    file.open (table); 
    if(file){    
        return file;
    }  
    else{  
        return empty; 
    }  
};

std::string TableFile::toString(){
    return this->table;
}