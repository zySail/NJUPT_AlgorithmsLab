#include <regex>
#include <vector>

extern std::vector<std::string> functionNames;
extern std::vector<std::vector<std::string>> calledFunctionNames;

extern std::regex singleLineComment;
extern std::regex funcDefPattern;
extern std::regex funcCallPattern;

void removecomment(std::string src, std::string dst);
std::vector<std::string> parseFuncDef(std::string fileName);
std::vector<std::vector<std::string>> parseFuncCall(std::string fileName);

void printRelationship(void);

