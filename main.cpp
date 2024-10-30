#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
//#include <sstream>
//#include <string>
#include "parse.h"

// std::vector<std::string> functionNames;
// std::vector<std::vector<std::string>> calledfunctionNames;


int main(){
    //std::string testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c";
    //std::string new_testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//newtest.c";
    std::string testFile = "test.c";
    std::string new_testFile = "newtest.c";
    // removecomment(testFile, new_testFile)

    parseFuncDef(new_testFile);
    parseFuncCall(new_testFile);
    printRelationship();
    
    return 0;
}

