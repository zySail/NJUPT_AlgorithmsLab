#include "parse.h"
#include "graph.h"

int main(){
#ifdef mytest
    std::string testFile = "..\\testfile\\mytest.c";
    std::string new_testFile = "..\\testfile\\newmytest.c";
#else
    std::string testFile = "..\\testfile\\test.c";
    std::string new_testFile = "..\\testfile\\newtest.c";
#endif
    removecomment(testFile, new_testFile);

    parseFuncDef(new_testFile);
    parseFuncCall(new_testFile);
    
    createGraph();
    findRecFunc();
    setMaxCallTimes();
    analyzeRec();

    return 0;
}

