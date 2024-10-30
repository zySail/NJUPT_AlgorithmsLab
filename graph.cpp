#include <iostream>
#include "graph.h"
#include "parse.h"

std::vector<std::vector<int>> matrix;
std::vector<int> RecFuncNum;
int size;

void createGraph(void){
    size = functionNames.size();
    matrix.resize(size, std::vector<int>(size, 0));
    for(int i = 0; i < functionNames.size(); i++){
        for(const std::string &funName : calledFunctionNames[i]){
            int j = getFuncNum(funName);
            matrix[i][j] = 1;
        }
    }
}

void printGraph(void){
    for(const auto &s : functionNames){
        std::cout << s << "  ";
    }
    std::cout << std::endl;
    for(const auto &row : matrix){
        for(const auto &element : row){ 
            std::cout << element << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void dfs(int v, int visit[]){
    for(int i = 1; i < size; i++){
        if(matrix[v][i] == 1 && visit[i] == 0){
            visit[i] = 1;
            dfs(i, visit);
        }
    }
}

bool isRec(int v){
    if(matrix[v][v] == 1)
        return true;
    int visit[size] = {0};
    dfs(v, visit);
    std::cout << v << ": ";
    for(int i = 1; i < size; i++) {
        std::cout << visit[i] << " ";
    }
    std::cout << std::endl;
    if(visit[v] == 1)
        return true;
    return false;
}

void findRecFunc(void){
    for(int i = 1; i < size; i++){
        if(isRec(i))
            RecFuncNum.push_back(i);
    }
    std::cout << "Recursive Functions:" << std::endl;
    for(const int &i : RecFuncNum){
        std::cout << functionNames[i] << std::endl;
    }
}

