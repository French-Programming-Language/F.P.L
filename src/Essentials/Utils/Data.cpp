#include "Data.h"

#include <utility>

namespace FPL::Data {
    Data::Data(std::vector<FPL::Tokenizer::Token>& Tokens) {
        AllFPLTypes["entier"] = FPL::Types::Types("entier", Types::BUILTIN_TYPE::INT);
        AllFPLTypes["decimal"] = FPL::Types::Types("decimal", Types::BUILTIN_TYPE::DOUBLE);
        AllFPLTypes["texte"] = FPL::Types::Types("texte", Types::BUILTIN_TYPE::STRING);
        AllFPLTypes["auto"] = FPL::Types::Types("auto", Types::BUILTIN_TYPE::AUTO);
        AllFPLTypes["bool"] = FPL::Types::Types("bool", Types::BUILTIN_TYPE::BOOL); // Deux façons d'avoir le type bool.
        AllFPLTypes["boolean"] = FPL::Types::Types("boolean", Types::BUILTIN_TYPE::BOOL);

        current_token = Tokens.begin();
        end_token = Tokens.end();

        InstructionsList = {
                // Instructions:
                "envoyer",
                "variable",
                "saisir",
                // Types:
                "entier",
                "decimal",
                "texte",
                "auto",
                "bool",
                "boolean",
        };
    }

    void Data::addVariableToMap(std::string& name, std::string& value, FPL::Types::Types& type, bool del, bool globale) {
        VariableDef newVariable;
        newVariable.VariableName = name;
        newVariable.VariableValue = value;
        newVariable.VariableType = type;
        newVariable.NeedDelete = del;
        newVariable.IsGlobal = globale;
        Map_Variables[newVariable.VariableName] = newVariable;
    }

    bool Data::isVariable(std::string& name) const {
        if (Map_Variables.contains(name)) { return true; }
        return false;
    }

    std::optional<FPL::VariableDef> Data::getVariable(std::string& name) {
        if (isVariable(name)) {
            VariableDef var = Map_Variables[name];
            return var;
        }
        return std::nullopt;
    }

    std::vector<Token>::iterator Data::incrementeAndGetToken(FPL::Data::Data& data) {
        data.current_token++;
        return data.current_token;
    }

    void Data::decrementeTokens(Data &data) {
        data.current_token--;
    }

    void Data::incrementeTokens(FPL::Data::Data &data) {
        data.current_token++;
    }

    void Data::updateValue(std::string &name, std::basic_string<char> value) {
        if (isVariable(name)) {
            Map_Variables[name].VariableValue = std::move(value);
        }
    }

    void Data::updateType(std::string& name, std::string& TypeName, Types::BUILTIN_TYPE Type) {
        if (isVariable(name)) {
            Map_Variables[name].VariableType.Name = TypeName;
            Map_Variables[name].VariableType.Type = Type;
        }
    }

    std::optional<FPL::FonctionDef> Data::getFonction(std::string& name) {
        return this->Map_Fonctions[name];
    }
}