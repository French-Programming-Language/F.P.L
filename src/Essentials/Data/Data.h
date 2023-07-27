#pragma once

#include <iostream>
#include <string_view>
#include <string>
#include <map>
#include <vector>
#include <optional>

#include "../Tokenizer/Tokenizer.h"
#include "../Definitions/Variables/Variables.h"
#include "../Definitions/Fonctions/Fonctions.h"

using namespace FPL::Definition::Variables;

namespace FPL::Essential::Data {
    class Data {
    public:
        std::map<std::string, Variable> Variables; // Nom Variable, Object &Variable
        std::map<std::string, FPL::Definition::Fonctions::Fonction> Fonctions; // Nom Variable, Object &Variable

        std::optional<Variable> getVariable(const std::string& name);
        bool variableExist(const std::string& name);
        bool variableExist(Variable v);
        void pushVariable(Variable var);
        void updateVariableValue(Variable var, const std::string& v);
        void deleteVariableFromMap(Variable var);

        std::optional<FPL::Definition::Fonctions::Fonction> getFonction(const std::string& name);
        std::optional<FPL::Definition::Fonctions::Argument> getFonctionArgument(const std::string& functionName, const std::string& argName);
        bool isFonction(const std::string& name);
        bool isFonctionArgument(const std::string& functionName, const std::string& argName);
        void pushFonction(FPL::Definition::Fonctions::Fonction f);
    };
}