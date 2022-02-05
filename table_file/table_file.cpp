using namespace std;
#include <sys/stat.h>
#include <iostream> 
#include <fstream> 
#include "table_file.h"

TableFile::TableFile(std::string _table): table(_table){}

bool TableFile::exist(){

    struct stat buffer;
    //check if directory exit
    if (stat(table.c_str(), &buffer) != 0) {
    	std::cout << "Directory doesn't exist!";
        return 0;
    } else {
    	std::cout << "Directory exists!";
        return 1;
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
