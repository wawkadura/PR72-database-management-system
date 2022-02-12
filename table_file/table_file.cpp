using namespace std;
#include <sys/stat.h>
#include <iostream> 
#include <fstream> 
#include "table_file.h"
#include "error/query_error_exception.h"

TableFile::TableFile(std::string _table): table(_table){};

void TableFile::exist(){

    struct stat buffer;
    //check if directory exit
    if (stat(table.c_str(), &buffer) != 0) {
    	cout << "Directory doesn't exist!";
        throw(QueryErrorException("Directory doesn't exist!"));
    } else {
    	cout << "Directory exists!";
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

void TableFile::open(){
    ofstream file;  
    file.open (table);  //file open
    if(file.is_open()){    
        cout<<"File close successfully."<<endl;  
    }  
    else{  
        cout<<"Error in file opening"<<endl;  
    }  
};
