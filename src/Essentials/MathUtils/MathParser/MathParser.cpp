#include "MathParser.h"

bool MATHPARSER_hasElement(std::vector<MathParser::Token>& array, std::string const& element) {
    for (auto const& e : array) {
        if (e.TokenText == element) {
            return true;
        }
    }
    return false;
}

int MATHPARSER_expectElement(std::vector<MathParser::Token>& array, std::string const& element) {
    for (MathParser::Token const& e : array) {
        if (e.TokenText == element) {
            auto it = std::find(begin(array), end(array), e);
            return (int) std::distance(array.begin(), it);
        }
    }
    return 0;
}

void MATHPARSER_operations(std::vector<MathParser::Token>& array, int& caseVector, std::string const& op) {
    MathParser::Token n1 = array[caseVector - 1];
    MathParser::Token n2 = array[caseVector + 1];

    double result = 0;

    if (op == "-") {
        result = n1 - n2;
    } else if (op == "+") {
        result = n1 + n2;
    } else if (op == "*") {
        result = n1 * n2;
    } else if (op == "/") {
        result = n1 / n2;
    }

    array[caseVector - 1].TokenText = std::to_string(result);
    array[caseVector].TokenText = "N/A";
    array[caseVector + 1].TokenText = "N/A";

    while (MATHPARSER_hasElement(array, "N/A")) {
        for (MathParser::Token const& e : array) {
            if (e.TokenText == "N/A") {
                auto it = std::find(begin(array), end(array), e);
                array.erase(it);
            }
        }
    }
}

double MATHPARSER_Parser(std::vector<MathParser::Token> contentSplitted) {
    int totalSizeVector = contentSplitted.size();
    int i = 0;

    while (i < totalSizeVector) {

        while (MATHPARSER_hasElement(contentSplitted, "*")) {
            auto caseVectorMulti = MATHPARSER_expectElement(contentSplitted, "*");
            MATHPARSER_operations(contentSplitted, caseVectorMulti, "*");
        }


        while (MATHPARSER_hasElement(contentSplitted, "/")) {
            auto caseVectorDiv = MATHPARSER_expectElement(contentSplitted, "/");
            MATHPARSER_operations(contentSplitted, caseVectorDiv, "/");
        }

        while (MATHPARSER_hasElement(contentSplitted, "+")) {
            auto caseVectorAdd = MATHPARSER_expectElement(contentSplitted, "+");
            MATHPARSER_operations(contentSplitted, caseVectorAdd, "+");
        }

        while (MATHPARSER_hasElement(contentSplitted, "-")) {
            auto caseVectorRemove = MATHPARSER_expectElement(contentSplitted, "-");
            MATHPARSER_operations(contentSplitted, caseVectorRemove, "-");
        }
        i++;
    }

    return convertDouble(contentSplitted[0].TokenText);
}