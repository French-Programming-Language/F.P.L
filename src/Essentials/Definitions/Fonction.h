#pragma once

#include <iostream>
#include <vector>
#include <ostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <optional>

#include "../Types.h"

namespace FPL {
    class FonctionArgumentDef {
    public:
        std::string ArgumentName;
        std::string ArgumentValue;
        Types::Types ArgumentType;

        friend std::ostream& operator<<(std::ostream& flux, FonctionArgumentDef const& arg);
        friend bool operator==(FonctionArgumentDef const& arg1, FonctionArgumentDef const& arg2);
    };

    class FonctionDef {
    public:
        FonctionDef();
        FonctionDef(std::string name, Types::Types type, std::map<std::string, FonctionArgumentDef> allArgs, std::vector<std::string> code, int nArgs, std::string returnV);

        std::string FonctionName;
        Types::Types FonctionType;
        std::map<std::string, FonctionArgumentDef> AllFonctionArguments;
        std::vector<std::string> FonctionContentCode;
        int FonctionNumberArgument = 0;
        std::string ReturnValue = "N/A";

        friend std::ostream& operator<<(std::ostream& flux, FonctionDef const& var);
        friend bool operator==(const FonctionDef &v1, const FonctionDef &v2);
        friend bool operator!=(const FonctionDef &v1, const FonctionDef &v2);

        bool isArgument(std::string const& argument);
        std::optional<FonctionArgumentDef> getArgument(std::string const& argument);
        void updateValueOfArgument(FonctionArgumentDef argument, std::string_view value);
    };
}