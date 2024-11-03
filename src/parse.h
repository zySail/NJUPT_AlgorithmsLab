#include <regex>
#include <vector>

extern std::vector<std::string> functionNames;
extern std::vector<std::vector<std::string>> calledFunctionNames;

void removecomment(std::string src, std::string dst);
void parseFuncDef(std::string fileName);
void parseFuncCall(std::string fileName);
int getFuncNum(const std::string &funcName);


