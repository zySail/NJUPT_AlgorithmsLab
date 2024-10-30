#include <regex>
#include <vector>

extern std::vector<std::string> functionNames;
extern std::vector<std::vector<std::string>> calledFunctionNames;
//extern std::map<std::string, int> Name2Num;

void removecomment(std::string src, std::string dst);
// std::vector<std::string> parseFuncDef(std::string fileName);
// std::vector<std::vector<std::string>> parseFuncCall(std::string fileName);
void parseFuncDef(std::string fileName);
void parseFuncCall(std::string fileName);
int getFuncNum(const std::string &funcName);

void printRelationship(void);

