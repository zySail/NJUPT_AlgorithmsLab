#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
//#include <sstream>
//#include <string>
#include "parse.h"

//using namespace std;

std::vector<std::string> functionNames;
std::vector<std::vector<std::string>> calledfunctions;


int main(){
    //std::string testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c";
    //std::string new_testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//newtest.c";
    std::string testFile = "test.c";
    std::string new_testFile = "newtest.c";
    // removecomment(testFile, new_testFile)

    functionNames = parseFuncDef(new_testFile);
    for(const std::string &s : functionNames){
        std::cout << s << std::endl;
    }

    // for(size_t i = 0; i < functions.size(); i++){
    //     std::cout << functions[i] << std::endl;
    //     for(const std::string &str : calledfunctions[i]){
    //         std::cout << "--" << str << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}

