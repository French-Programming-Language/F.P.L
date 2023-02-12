#pragma once

#include <iostream>
#include <map>
#include <string>

#include "Types.h"

namespace FPL::Statement {

    enum class StatementKind: int {
        VARIABLE_DECLARATION,
        FUNCTION_CALL,
        LITTERAL
    };

    inline constexpr const char* sStatementKindStrings[] = {
            "VARIABLE_DECLARATION",
            "FUNCTION_CALL",
            "LITTERAL"
    };

    class Statement {
    public:
        Statement();
        Statement(StatementKind kind, std::string name, FPL::Types::Types type);

        std::string StatementName;
        FPL::Types::Types StatementType{FPL::Types::Types("vide", FPL::Types::BUILTIN_TYPE::VOID)};
        StatementKind kind{};
    };
}