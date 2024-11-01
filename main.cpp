#include "parse.h"
#include "graph.h"
//#include <cstdlib>

int main(){
    std::string testFile = "test.c";
    std::string new_testFile = "newtest.c";
    removecomment(testFile, new_testFile);

    parseFuncDef(new_testFile);
    parseFuncCall(new_testFile);
    
    createGraph();
    findRecFunc();
    setMaxCallTimes();
    analyzeRec();
    
    //system("dot -Tpng graph.dot -o graph.png");

    return 0;
}

