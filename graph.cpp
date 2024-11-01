#include <iostream>
#include "graph.h"
#include "parse.h"

int size; // matirx size
std::vector<std::vector<int>> matrix; // adj matrix
std::vector<int> recFuncNum; // store recursive function numbers
std::vector<int> MaxCallTimes; // store a function max call time
std::vector<int> maxDepth; // record maxdepth a function can arrive 
std::vector<int> callTimes; // record a function call time

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
    // std::cout << v << ": ";
    // for(int i = 1; i < size; i++) {
    //     std::cout << visit[i] << " ";
    // }
    // std::cout << std::endl;
    if(visit[v] == 1)
        return true;
    return false;
}

void findRecFunc(void){
    for(int i = 1; i < size; i++){
        if(isRec(i))
            recFuncNum.push_back(i);
    }
    std::cout << "Recursive Functions:" << std::endl;
    for(const int &i : recFuncNum){
        std::cout << functionNames[i] << std::endl;
    }
    std::cout << std::endl;
}

void setMaxCallTimes(void){
    // MaxCallTimes.resize(size, 0);
    // for(int i = 1; i < size; i++){
    //         std::cout << "set " << functionNames[i] << " max call times: ";
    //         std::cin >> MaxCallTimes[i];
    // }
    MaxCallTimes = {0,4,3,1,5};
    std::cout << "max call times: ";
    for(int i = 1; i < size; i++){
        std::cout << MaxCallTimes[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void dfs_depth(int v, int depth){
    if(depth > maxDepth[v])
        maxDepth[v] = depth;
    if(callTimes[v] < MaxCallTimes[v])
        callTimes[v]++;
    
    for(int i = 1; i < size; i++){
        if((matrix[v][i] == 1) && (callTimes[i] + 1 <= MaxCallTimes[i])){
            dfs_depth(i, depth+1);
        }
    }    
}

void recordFuncCall(int start){ // record func call Times and max depth from func start
    dfs_depth(start, 1);
    return;
}

void analyzeRec(void){
    maxDepth.resize(size, 0);
    callTimes.resize(size, 0);
    for(int i = 1; i < size; i++){
        if(matrix[0][i] == 1){
            recordFuncCall(i);
        }
    }
    // printf rec funcs' call times and max depth
    std::cout << "Function Call Statistics:" << std::endl;
    for(const int i : recFuncNum){
        std::cout << functionNames[i] << " Called " << callTimes[i] << " times, Max Depth: " << maxDepth[i] << std::endl;
    }
}

