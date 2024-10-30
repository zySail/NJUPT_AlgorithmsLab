#include <iostream>
#include "graph.h"
#include "parse.h"

std::vector<std::vector<int>> matrix;

void createMatrix(void){
    int size = functionNames.size();
    matrix.resize(size, std::vector<int>(size, 0));
    for(size_t i = 0; i < functionNames.size(); i++){
        for(const std::string &funName : calledFunctionNames[i]){
            int j = getFuncNum(funName);
            matrix[i][j] = 1;
        }
    }
}

void printMatrix(void){
    for(const auto &row : matrix){
        for(const auto &element : row){ 
            std::cout << element << "  ";
        }
        std::cout << std::endl;
    }
}