#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

std::ifstream test;

string removeComments(const string &code) {
    regex singleLineComment(R"(//.*?$)");
    return regex_replace(code, singleLineComment, "");
}

void readline(){
    std::string s;
    while(getline(test,s)){
    	s = removeComments(s); 
        std::cout << s << std::endl;
    }
    return;
}


int main(){
    test.open("D://Programming//Algorithms//NJUPT_AlgorithmsLab//problem6//test.c", std::ios::in);
    if(!test.is_open()){
        std::cout << "can not open test file" << std::endl;
        return 0;
    }
    readline();
    test.close();
    return 0;
}
