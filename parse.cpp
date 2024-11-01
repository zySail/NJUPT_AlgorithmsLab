#include "parse.h"
#include <iostream>
#include <fstream>

std::vector<std::string> functionNames; // store function names
std::vector<std::vector<std::string>> calledFunctionNames; // store the called function names
void printRelationship(void);

std::regex singleLineComment(R"(//.*?$)");
std::regex funcDefPattern(R"((?:int|float|double|void|char)\s*([a-zA-Z_]\w*)\s*\([^)]*\)\s*\{)");
std::regex funcCallPattern(R"(([a-zA-Z_]\w*)\s*\([^)]*\)\s*;)");

std::string removeSingleComment(const std::string &s){
    return regex_replace(s, singleLineComment, "");
}

std::string detectFuncDef(const std::string &line){
    std::smatch matchs;
    if(regex_search(line, matchs, funcDefPattern)){
        return matchs[1];
    }
    return "";
}

std::string detectFuncCall(const std::string &s){
    std::smatch matchs;
    if(regex_search(s, matchs, funcCallPattern)){
        return matchs[1];
    }
    return "";   
}


// read src file, remove comments and write into dst file
void removecomment(std::string src, std::string dst){
#ifdef DEBUG
    return;
#else   
    std::ifstream srcfile;
    std::ofstream dstfile;
    srcfile.open(src, std::ios::in);
    if(!srcfile.is_open()){
        std::cerr << "can not open src file" << std::endl;
    }
    dstfile.open(dst, std::ios::trunc);
    if(!srcfile.is_open()){
        std::cerr << "can not open dst file" << std::endl;
    }

    std::string line;
    while(getline(srcfile, line)){
        line = removeSingleComment(line);
        dstfile << line << std::endl;
    }

    srcfile.close();
    dstfile.close();
    return;
#endif
}

// open file, detect all function definitions and store them in vector
void parseFuncDef(std::string fileName){
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if(!file.is_open()){
        std::cerr << "can not open src file" << std::endl;
    }

    std::string line;
    std::string funcName;
    while(getline(file, line)){
        funcName = detectFuncDef(line);
        if(!funcName.empty()){
            functionNames.push_back(funcName);
        }
    }

    file.close();
    return;
}


// open file, get all function calls after detecting a function definition and store them in vector
void parseFuncCall(std::string fileName){
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if(!file.is_open()){
        std::cerr << "can not open src file" << std::endl;
    }

    std::string line;
    std::string funcName;
    calledFunctionNames.resize(functionNames.size());
    int n = -1;
    while(getline(file, line)){
        funcName = detectFuncDef(line);
        if(!funcName.empty()){ // when detect a function def, pointer to next vector 
            n++;
            continue;
        }
        funcName = detectFuncCall(line);
        if(!funcName.empty()){
            calledFunctionNames[n].push_back(funcName);
        }
    }
    file.close();
#ifdef DEBUG
    printRelationship();
#else
#endif
    return;
}

void printRelationship(void){
    std::cout << "function call relationship:" << std::endl;
    for(size_t i = 0; i < functionNames.size(); i++){
        std::cout << functionNames[i] << std::endl;
        for(const std::string &str : calledFunctionNames[i]){
            std::cout << "--" << str << std::endl;
        }
        std::cout << std::endl;
    }
}

int getFuncNum(const std::string &funcName){
    for (size_t i = 0; i < functionNames.size(); ++i) {
        if (functionNames[i] == funcName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}