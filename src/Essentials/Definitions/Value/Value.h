#pragma once

#include <iostream>
#include "../Types/Types.h"

namespace FPL::Definition::Values {
    class Value {
    public:
        Value();
        Value(Types::Type type, std::string content);

        Types::Type type;
        std::string content;
    };
}