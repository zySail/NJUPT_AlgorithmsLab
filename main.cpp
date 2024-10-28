#include <iostream>
#include <fstream>
#include <unistd.h>

int main(){
    char buffer[256];
    getcwd(buffer, 256);
    std::cout << "Current working directory: " << buffer << std::endl;
    std::ifstream test;
    test.open("D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c", std::ios::in);
    if(!test.is_open()){
        std::cout << "can not open test file" << std::endl;
        return 0;
    }
    std::string s;
    while(getline(test,s)){
        std::cout << s << std::endl;
    }
    test.close();
    return 0;
}