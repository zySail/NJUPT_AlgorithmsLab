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

bool removecomment(std::string src, std::string dst);

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
    string testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c";
    string new_testFile = "D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//newtest.c";
    if(!removecomment(testFile, new_testFile)){
        std::cout << "error" << std::endl;
        return 0;
    }
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
        cout << functions[i] << endl;
        for(const string &str : calledfunctions[i]){
            cout << "--" << str << endl;
        }
        cout << endl;
    }

    test.close();
    return 0;
}

string removeSingleComment(const string &s){
    return regex_replace(s, singleLineComment, "");
}

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