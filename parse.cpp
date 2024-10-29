#include "parse.h"
#include <iostream>
#include <fstream>

std::string removeSingleComment(const std::string &s){
    return regex_replace(s, singleLineComment, "");
}

// read src file, remove comments and write into dst file
bool removecomment(std::string src, std::string dst){
    std::ifstream srcfile;
    std::ofstream dstfile;
    srcfile.open(src, std::ios::in);
    if(!srcfile.is_open()){
        std::cout << "can not open src file" << std::endl;
        return false;
    }
    dstfile.open(dst, std::ios::trunc);
    if(!srcfile.is_open()){
        std::cout << "can not open dst file" << std::endl;
        return false;
    }

    std::string line;
    while(getline(srcfile, line)){
        line = removeSingleComment(line);
        dstfile << line << std::endl;
    }

    srcfile.close();
    dstfile.close();
    return true;
}