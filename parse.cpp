#include "parse.h"
#include <iostream>
#include <fstream>

std::regex singleLineComment(R"(//.*?$)");
std::regex funcDefPattern(R"((?:int|float|double|void|char)\s*([a-zA-Z_]\w*)\s*\([^)]*\)\s*\{)");
std::regex funcCallPattern(R"(([a-zA-Z_]\w*)\s*\([^)]*\)\s*;)");

std::string removeSingleComment(const std::string &s){
    return regex_replace(s, singleLineComment, "");
}

std::string detectFuncDef(const std::string &line){
    std::smatch matchs;
    if(regex_search(line, matchs, funcDefPattern)){
        //cout << "define: " << matchs[1] << endl;
        return matchs[1];
    }
    return "";
}

std::string detectFuncCall(const std::string &s){
    std::smatch matchs;
    if(regex_search(s, matchs, funcCallPattern)){
        //cout << "--called: " << matchs[1] << endl;
        return matchs[1];
    }
    return "";   
}


// read src file, remove comments and write into dst file
void removecomment(std::string src, std::string dst){
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
}


// open file, detect all function definitions and store them in vector
std::vector<std::string> parseFuncDef(std::string fileName){
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if(!file.is_open()){
        std::cerr << "can not open src file" << std::endl;
    }

    std::string line;
    std::string funcName;
    std::vector<std::string> functions;
    while(getline(file, line)){
        funcName = detectFuncDef(line);
        if(!funcName.empty()){
            functions.push_back(funcName);
        }
    }

    file.close();

    return functions;
}


// open file, detect all function calls after a function definition and store them in vector
std::vector<std::vector<std::string>> getFuncCall(std::string fileName){

}