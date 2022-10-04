#pragma once

#include <string>

namespace FPL {
    enum BUILTIN_TYPE {
        VIDE,
        INT,
        DOUBLE,
        STRING,
        BOOL,
        AUTO
        // STRUCT -> pour l'oo
    };

    class Type {
    public:
        explicit Type(const std::string &name = "", const enum BUILTIN_TYPE type = VIDE) : mName(name), mType(type){};

        std::string mName;
        enum BUILTIN_TYPE mType;
        // std::vector<Type> mField; -> pour le struct
    };
}