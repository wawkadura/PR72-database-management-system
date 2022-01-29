#include "table_file.h"
using namespace std;
#include <sys/stat.h>
#include <iostream> 
#include <fstream> 


TableFile::TableFile(): source_file("/toto.txt"){
    // return Table_file(nul);
}

bool TableFile::exist(){

    struct stat buffer;
    if (stat(source_file.c_str(), &buffer) != 0) {
    	std::cout << "Directory doesn't exist!";
        return 0;
    } else {
    	std::cout << "Directory exists!";
        return 1;
    }
    
};

void TableFile::close(){
    ofstream file;  
    file.open (source_file);  
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
    file.open (source_file);  
    if(file.is_open()){    
        cout<<"File close successfully."<<endl;  
    }  
    else{  
        cout<<"Error in file opening"<<endl;  
    }  
};
