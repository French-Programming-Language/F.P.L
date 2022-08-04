#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>
#include <optional>
#include <map>
#include <functional>
#include <algorithm>

#include "TokenBuilding.h"
#include "TypeManager.h"
#include "FonctionDefinition.h"
#include "VariableDefinition.h"

namespace FPL {

    class Parser {
    public:
        Parser();

        void parse(std::vector<Token> &tokens, std::optional<FonctionDefinition>& fonction);

        [[maybe_unused]] void DebugPrint() const;

    private:
        // Essentielles:
        std::optional<Type> CheckerType();
        std::optional<Token> CheckerIdentifiant(std::string_view name = std::string());
        std::optional<Token> CheckerOperateur(std::string_view name = std::string());
        std::optional<Statement> CheckerValue();


        // Print :
        bool PrintInstruction(auto parseStart, std::optional<FonctionDefinition>& fonction);

        // Variable :
        std::map<std::string, VariableDefinition> mVariables;
        bool isVariable(std::string &name) const;
        bool executeInputs(std::optional<FonctionDefinition> &fonction, std::string& VarName, Type& VarType, std::string option);
        void ManageVariableName(std::optional<FonctionDefinition> &fonction, std::string name);
        void DefineVariable(std::optional<FonctionDefinition> &fonction, std::string &VarName, Type &VarType, std::string &VarValue);
        bool VariableInstruction(std::optional<FonctionDefinition>& fonction);
        bool ChangerInstruction(std::optional<FonctionDefinition>& fonction);
        bool SaisirInstruction(std::optional<FonctionDefinition>& fonction);

        // Fonctions :
        std::map<std::string, FonctionDefinition> mFonctions;
        std::map<std::string, std::map<std::string, ArgumentDefinition>> mArguments;
        bool FonctionInstruction(auto parseStart);
        bool AppelerInstruction();
        void executeFonctionContent(FonctionDefinition &fonction, std::string fonctionName);
        bool isFonction(std::string &name) const;
        bool isFonctionArgument(std::string &fonction, std::string &argument);
        bool isArgument(std::string& fonction, std::string &name) const;
        std::optional<FonctionDefinition> getFonction(std::string &fonction);
        std::optional<ArgumentDefinition> getArgument(std::string &fonction, std::string &name);


        // Utils :
        bool ManagerInstruction(std::optional<FonctionDefinition>& fonction);
        std::vector<Token>::iterator mCurrentToken;
        std::vector<Token>::iterator mEndToken;
        std::map<std::string, Type> mTypes;
        std::vector<std::string> InstructionsList;
    };
}