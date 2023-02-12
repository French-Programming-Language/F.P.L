#pragma once

#include <iostream>
#include <vector>
#include <ostream>
#include <string>

#include "../Types.h"

namespace FPL {
    class VariableDef {
    public:
        std::string VariableName;
        Types::Types VariableType;
        std::string VariableValue;
        bool NeedDelete = false;
        bool IsGlobal = false;

        friend std::ostream& operator<<(std::ostream& flux, VariableDef const& var);

        friend bool operator==(const VariableDef &v1, const VariableDef &v2);
        friend bool operator!=(const VariableDef &v1, const VariableDef &v2);
    };
}