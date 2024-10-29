#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
//#include <sstream>
//#include <string>

using namespace std;

std::ifstream test;
vector<string> functions;
vector<vector<string>> calledfunctions;
vector<string> tmp;

regex singleLineComment(R"(//.*?$)");
regex funcDefPattern(R"((?:int|float|double|void|char)\s*([a-zA-Z_]\w*)\s*\([^)]*\)\s*\{)");
regex funcCallPattern(R"(([a-zA-Z_]\w*)\s*\([^)]*\)\s*;)");

string removeComments(const string &s){
    return regex_replace(s, singleLineComment, "");
}

bool detectFuncDef(const string &s){
    smatch matchs;
    if(regex_search(s, matchs, funcDefPattern)){
        //cout << "define: " << matchs[1] << endl;
        functions.push_back(matchs[1]);
        return true;
    }
    return false;
}

void detectFuncCall(const string &s){
    smatch matchs;
    if(regex_search(s, matchs, funcCallPattern)){
        //cout << "--called: " << matchs[1] << endl;
        tmp.push_back(matchs[1]);
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
    int funcN = 0;
    while(getline(test,s)){
    	s = removeComments(s); 
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
        cout << functions[i] << endl;
        for(const string &str : calledfunctions[i]){
            cout << "--" << str << endl;
        }
        cout << endl;
    }

    test.close();
    return 0;
}