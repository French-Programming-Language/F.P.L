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
        std::string FonctionName;
        Types::Types FonctionType;
        std::map<std::string, FonctionArgumentDef> AllFonctionArguments;
        std::vector<std::string> FonctionContentCode;
        int FonctionNumberArgument = 0;
        std::string ReturnValue = "N/A";

        friend std::ostream& operator<<(std::ostream& flux, FonctionDef const& var);

        bool isArgument(std::string const& argument);
        std::optional<FonctionArgumentDef> getArgument(std::string const& argument);
        void updateValueOfArgument(FonctionArgumentDef argument, std::string_view value);
    };
}