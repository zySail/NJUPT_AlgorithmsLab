#include "parse.h"
#include "graph.h"

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
    drawFuncCall();

    return 0;
}

