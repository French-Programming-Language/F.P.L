#include "FunctionsUtils.h"

std::string FPL::Instruction::FunctionUtils::ReturnStringVector(std::vector<std::string> vector) {
    std::stringstream result_STR;
    for (auto it = vector.begin(); it != vector.end(); it++)    {
        if (it != vector.begin()) {
            result_STR << " ";
        }
        result_STR << *it;
    }
    return result_STR.str();
}