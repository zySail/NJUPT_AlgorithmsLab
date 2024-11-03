#include "parse.h"
#include "graph.h"

int main(){
    std::string testFile = "testfile\\test.c";
    std::string new_testFile = "testfile\\newtest.c";
    removecomment(testFile, new_testFile);

    parseFuncDef(new_testFile);
    parseFuncCall(new_testFile);
    
    createGraph();
    findRecFunc();
    setMaxCallTimes();
    analyzeRec();

    return 0;
}

