#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Utils/Converts.h"
#include "MathTokenizer.h"

bool MATHPARSER_hasElement(std::vector<MathParser::Token>& array, std::string const& element);
int MATHPARSER_expectElement(std::vector<MathParser::Token>& array, std::string const& element);
void MATHPARSER_operations(std::vector<MathParser::Token>& array, int& caseVector, std::string const& op);
double MATHPARSER_Parser(std::vector<MathParser::Token> contentSplitted);