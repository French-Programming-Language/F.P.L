#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <optional>
#include <map>
#include <functional>
#include <fstream>

#include "TokenBuilding.h"
#include "TypeManager.h"
#include "FonctionDefinition.h"
#include "VariableDefinition.h"

#include "Utils/Converts.h"

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

        void ManageVariableName(std::optional<FonctionDefinition> &fonction, std::string name);
        void DefineVariable(std::optional<FonctionDefinition>& fonction, std::string& VarName, Type& VarType, std::string& VarValue, std::optional<Statement>& ContentVarValue, bool isGlobal, bool HasReturnV);
        bool VariableInstruction(std::optional<FonctionDefinition>& fonction);
        bool ChangerInstruction(std::optional<FonctionDefinition>& fonction);
        bool ConversionInstruction(std::optional<FonctionDefinition>& fonction);

        // Inputs:
        bool SaisirInstruction(std::optional<FonctionDefinition>& fonction);
        bool executeInputs(std::optional<FonctionDefinition> &fonction, std::string& VarName, Type& VarType, const std::string& option);

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

        // Conditions:
        bool VerifierInstruction(std::optional<FonctionDefinition>& fonction);

        // Boucles:
        bool TantQueInstruction(std::optional<FonctionDefinition>& fonction);

        // Fichiers :
        bool FichierInstruction(std::optional<FonctionDefinition>& fonction);

        // Imports :
        bool ImportInstruction(std::optional<FonctionDefinition>& fonction);

        // Utils :
        bool ManagerInstruction(std::optional<FonctionDefinition>& fonction);
        std::vector<Token>::iterator mCurrentToken;
        std::vector<Token>::iterator mEndToken;
        std::map<std::string, Type> mTypes;
        std::vector<std::string> InstructionsList;
    };
}