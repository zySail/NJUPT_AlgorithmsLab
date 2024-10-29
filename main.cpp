#include <iostream>
#include <fstream>
#include <vector>
//#include <sstream>
//#include <string>
#include "parse.h"

//using namespace std;

std::ifstream test;
std::vector<std::string> functions;
std::vector<std::vector<std::string>> calledfunctions;
std::vector<std::string> tmp;


bool removecomment(std::string src, std::string dst);

bool detectFuncDef(const std::string &s){
    std::smatch matchs;
    if(regex_search(s, matchs, funcDefPattern)){
        //cout << "define: " << matchs[1] << endl;
        functions.push_back(matchs[1]);
        return true;
    }
    return false;
}

void detectFuncCall(const std::string &s){
    std::smatch matchs;
    if(regex_search(s, matchs, funcCallPattern)){
        //cout << "--called: " << matchs[1] << endl;
        tmp.push_back(matchs[1]);
    }
    return;   
}

int main(){
    std::string testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c";
    std::string new_testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//newtest.c";
    // if(!removecomment(testFile, new_testFile)){
    //     std::cout << "error" << std::endl;
    //     return 0;
    // }

    test.open(new_testFile, std::ios::in);
    if(!test.is_open()){
        std::cout << "can not open test file" << std::endl;
        return 0;
    }
    std::string s;
    int funcN = 0;
    while(getline(test,s)){ 
        if(detectFuncDef(s)){
            funcN++;
            if(funcN != 1){
                calledfunctions.push_back(tmp); // push the old func call
            }
            tmp.clear();
        }
        else{
            detectFuncCall(s);
        }
    }
    calledfunctions.push_back(tmp); // push the last func call
    tmp.clear();

    for(size_t i = 0; i < functions.size(); i++){
        std::cout << functions[i] << std::endl;
        for(const std::string &str : calledfunctions[i]){
            std::cout << "--" << str << std::endl;
        }
        std::cout << std::endl;
    }

    test.close();
    return 0;
}

