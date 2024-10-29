#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
//#include <sstream>
//#include <string>

using namespace std;

std::ifstream test;
vector<string> functions;

regex singleLineComment(R"(//.*?$)");
regex funcDefPattern(R"((?:int|float|double|void|char)\s*((?!main)\b[a-zA-Z_]\w*)\s*\([^)]*\)\s*\{)");
regex funcCallPattern(R"(([a-zA-Z_]\w*)\s*\([^)]*\)\s*;)");

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

void detectFuncCall(const string &s){
    smatch matchs;
    if (regex_search(s, matchs, funcCallPattern)) {
        cout << matchs[1] << endl;
        //functions.push_back(matchs[1]);
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
        detectFuncCall(s);
    }
    // for (const auto &funcName : functions) {
    //     cout << funcName << endl;
    // }
    test.close();
    return 0;
}
