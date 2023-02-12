#pragma once

#include <iostream>
#include <string>
#include <utility>

namespace FPL::Types {
    enum BUILTIN_TYPE {
        VOID,
        INT,
        DOUBLE,
        STRING,
        BOOL,
        AUTO
    };

    class Types {
    public:
        explicit Types(std::string name = "", const enum BUILTIN_TYPE type = VOID) : Name(std::move(name)), Type(type){}

        std::string Name;
        enum BUILTIN_TYPE Type;
    };
}