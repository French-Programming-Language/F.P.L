#pragma once

namespace FPL::Definition::Types {
    enum Type {
        INT,
        DOUBLE,
        STRING,
        BOOL,
    };
    inline constexpr const char *Types_STR[] =  {
            "INT",
            "DOUBLE",
            "STRING",
            "BOOL",
    };
}