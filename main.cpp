#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::ifstream test;
vector<string> functions;

regex singleLineComment(R"(//.*?$)");
//regex funcDefPattern("(?:int|float|double|void|char)\\s*([a-zA-Z_]\\w*)\\s*\\([^)]*\\)\\s*\\{");
regex funcDefPattern("(?:int|float|double|void|char)\\s*((?!main)\\b[a-zA-Z_]\\w*)\\s*\\([^)]*\\)\\s*\\{");
//regex funcCallPattern(R"(\b([a-zA-Z_]\w*)\s*\([^)]*\)\s*;)");

string removeComments(const string &s) {
    return regex_replace(s, singleLineComment, "");
}

void detectFuncDef(const string &s){
    smatch matchs;
    if (regex_search(s, matchs, funcDefPattern)) {
        //cout << matchs[1] << endl;
        functions.push_back(matchs[1]);
    }
    return;
}

int main(){
    test.open("D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c", std::ios::in);
    if(!test.is_open()){
        std::cout << "can not open test file" << std::endl;
        return 0;
    }
    std::string s;
    while(getline(test,s)){
    	s = removeComments(s); 
        detectFuncDef(s);
    }
    for (const auto &funcName : functions) {
        cout << funcName << endl;
    }
    test.close();
    return 0;
}
