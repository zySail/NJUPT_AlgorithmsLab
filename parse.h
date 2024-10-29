#include <regex>
#include <vector>

std::regex singleLineComment(R"(//.*?$)");
std::regex funcDefPattern(R"((?:int|float|double|void|char)\s*([a-zA-Z_]\w*)\s*\([^)]*\)\s*\{)");
std::regex funcCallPattern(R"(([a-zA-Z_]\w*)\s*\([^)]*\)\s*;)");


bool removecomment(std::string src, std::string dst);
std::vector<std::string> getFuncDef(std::string fileName);
std::vector<std::vector<std::string>> getFuncCall(std::string fileName);
