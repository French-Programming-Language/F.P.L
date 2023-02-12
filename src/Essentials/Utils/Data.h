#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <optional>

#include "../Types.h"
#include "../Tokenizer.h"
#include "../Definitions/Variables.h"
#include "../Definitions/Fonction.h"

namespace FPL::Data {
    using namespace FPL::Tokenizer;

    class Data {
    public:
        explicit Data(std::vector<FPL::Tokenizer::Token>& Tokens);

        std::vector<Token>::iterator current_token; // Le token que le Parser analyze
        std::vector<Token>::iterator end_token; // Le dernier token sauvegardé

        std::vector<Token>::iterator incrementeAndGetToken(FPL::Data::Data& data);
        void decrementeTokens(FPL::Data::Data& data);
        void incrementeTokens(FPL::Data::Data& data);

        std::map<std::string, FPL::Types::Types> AllFPLTypes;
        std::vector<std::string> InstructionsList;
        std::map<std::string, FPL::VariableDef> Map_Variables;
        std::map<std::string, FPL::FonctionDef> Map_Fonctions;

        void addVariableToMap(std::string& name, std::string& value, FPL::Types::Types& type, bool del, bool globale);
        bool isVariable(std::string& name) const;
        std::optional<FPL::VariableDef> getVariable(std::string& name);
        void updateValue(std::string &name, std::basic_string<char> value);
        void updateType(std::string& name, std::string& TypeName, Types::BUILTIN_TYPE Type);

        std::optional<FPL::FonctionDef> getFonction(std::string& name);
        bool HasReturnValue = false;
        std::string ReturnValue = "N/A";
        Types::Types ReturnType;
    };
}