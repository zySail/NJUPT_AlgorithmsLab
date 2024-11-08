#include <iostream>
#include <fstream>
#include <cstdlib>
#include "graph.h"
#include "parse.h"

int nNodes; 
std::vector<std::vector<int>> adjList; // adj list
std::vector<int> recFuncList; // store recursive function numbers
std::vector<int> MaxCallTimes; // store a function max call time
std::vector<int> maxDepth; // record maxdepth a function can arrive 
std::vector<int> callTimes; // record a function call time
std::vector<int> funcCallOrder; // record the order that function be called
std::ofstream dotFile;

void printGraph(void);
void drawFuncCall(void);
void draw_start(void);
void draw_write(void);
void draw_end(void);

void createGraph(void){
    nNodes = functionNames.size();
    adjList.resize(nNodes);
    for(int i = 0; i < nNodes; i++){
        for(const std::string &funName : calledFunctionNames[i]){
            adjList[i].push_back(getFuncNum(funName));
        }
    }
#ifdef DEBUG
    printGraph();
#else
#endif
    return;
}

void printGraph(void){
    std::cout << "grapt adj list:" << std::endl;
    for(int i = 0; i < nNodes; i++){
        std::cout << i << ": ";
        for(const int &n : adjList[i])
            std::cout << n << " ";
        std::cout << std::endl;
    }
    for(int i = 0; i < nNodes; i++){
        std::cout << functionNames[i] << ": ";
        for(const int &n : adjList[i])
            std::cout << functionNames[n] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void dfs(int v, int visit[]){
    for(const int &i : adjList[v]){
        if(visit[i] == 0){
            visit[i] = 1;
            dfs(i, visit);
        }
    }
}

bool isRec(int v){
    int visit[nNodes] = {0};
    dfs(v, visit);

#ifdef DEBUG
    std::cout << "function "<< v << " visit[]" << ": ";
    for(int i = 1; i < nNodes; i++) {
        std::cout << visit[i] << " ";
    }
    std::cout << std::endl;
#else
#endif

    if(visit[v] == 1)
        return true;
    return false;
}

void findRecFunc(void){
    for(int i = 1; i < nNodes; i++){
        if(isRec(i))
            recFuncList.push_back(i);
    }
    std::cout << "Recursive Functions:" << std::endl;
    for(const int &i : recFuncList){
        std::cout << functionNames[i] << std::endl;
    }
    std::cout << std::endl;
}

void setMaxCallTimes(void){
    MaxCallTimes.resize(nNodes, 0);
#ifdef DEBUG
    MaxCallTimes = {0,4,3,1,5,5};
#else
    for(int i = 1; i < nNodes; i++){
            std::cout << "set " << functionNames[i] << " max call times: ";
            std::cin >> MaxCallTimes[i];
    }
#endif
    std::cout << "max call times you set: ";
    for(int i = 1; i < nNodes; i++){
        std::cout << functionNames[i] << "(" << MaxCallTimes[i] << ") ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void dfs_depth(int v, int depth){
    funcCallOrder.push_back(v);
    if(depth > maxDepth[v])
        maxDepth[v] = depth;
    if(callTimes[v] < MaxCallTimes[v])
        callTimes[v]++;
    
    for(const int &i : adjList[v]){
        if(callTimes[i] + 1 <= MaxCallTimes[i]){
            dfs_depth(i, depth+1);
        }                                                                           
    }
    funcCallOrder.push_back(-1); // used to mark return times
}

void recordFuncCall(int start){ // record func call Times and max depth from func start
    funcCallOrder.clear();
    funcCallOrder.push_back(0);
    dfs_depth(start, 1);
    printCritialPath();
    draw_write();
    return;
}

void analyzeRec(void){
    maxDepth.resize(nNodes, 0);
    callTimes.resize(nNodes, 0);
    draw_start();
    for(const int i : adjList[0]){ // start from main call function
        recordFuncCall(i);
    }
    // printf rec funcs' call times and max depth
    std::cout << "Function Call Statistics:" << std::endl;
    for(const int i : recFuncList){
        if(i < 0) 
            continue;
        std::cout << functionNames[i] << " Called " << callTimes[i] << " times, Max Depth: " << maxDepth[i] << std::endl;
    }
    std::cout << std::endl;
    draw_end();
    //drawFuncCall();
}

void draw_start(void){
    dotFile.open("..\\output\\functionCall.dot", std::ios::trunc);
    if (!dotFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    dotFile << "digraph FunctionCalls {\n";
    dotFile << "\trankdir=TB;\n";
    dotFile << "\tnode [shape=ellipse];\n";
}

void draw_write(void){
    for (size_t i = 0; i < funcCallOrder.size(); ++i) {
        int currentFunc = funcCallOrder[i];
        if(currentFunc >= 0)
            dotFile << "\t" << functionNames[currentFunc] << i << " [lable=" << currentFunc << "];\n";

        if (i < funcCallOrder.size() - 1) {
            int nextFunc = funcCallOrder[i + 1];
            if(nextFunc >= 0)
                dotFile << "\t" << functionNames[currentFunc] << i <<  " -> " << functionNames[nextFunc] << i+1 << ";\n";
        }
    }
}

void draw_end(void){
    dotFile << "}\n";
    dotFile.close();
    std::cout << "draw complete" << std::endl;

    system("dot -Tpng ..\\output\\functionCall.dot -o ..\\output\\functionCall.png");
}

void printCritialPath(void){
    bool isReturning = false;
    std::cout << "关键路径: " << std::endl;
    for(size_t i = 0; i < funcCallOrder.size(); i++){
        if(funcCallOrder[i] < 0){
            if(!isReturning){
                std::cout << "end" << std::endl;
                isReturning = true;
            }
            else
                continue;
        }
        else{
            isReturning = false;
            std::cout << functionNames[funcCallOrder[i]] << "->";
        }
    }
    std::cout << std::endl;
}

// unused, split into draw_start, draw_write and draw_end
void drawFuncCall(void){
    dotFile.open("..\\output\\functionCall.dot", std::ios::in);
    if (!dotFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    dotFile << "digraph FunctionCalls {\n";
    dotFile << "\trankdir=TB;\n";
    dotFile << "\tnode [shape=ellipse];\n";

    for (size_t i = 0; i < funcCallOrder.size(); ++i) {
        int currentFunc = funcCallOrder[i];
        if(currentFunc >= 0)
            dotFile << "\t" << functionNames[currentFunc] << i << " [lable=" << currentFunc << "];\n";

        if (i < funcCallOrder.size() - 1) {
            int nextFunc = funcCallOrder[i + 1];
            if(nextFunc >= 0)
                dotFile << "\t" << functionNames[currentFunc] << i <<  " -> " << functionNames[nextFunc] << i+1 << ";\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();

    system("dot -Tpng ..\\output\\functionCall.dot -o ..\\output\\functionCall.png");
}

