#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <string_view>
#include <map>
#include <unordered_map>

#include "../Types/Types.h"
#include "../Value/Value.h"
#include "../../Tokenizer/Tokenizer.h"

namespace FPL::Definition::Fonctions {
    class Argument {
    public:
        Argument();
        Argument(std::string const& n, Types::Type const& t, Values::Value const& v);

        std::string getName();
        Types::Type getType();
        Values::Value getValue();

        void setName(std::string const& n);
        void setType(Types::Type const& t);
        void setValue(Values::Value const& v);

        friend std::ostream& operator<<(std::ostream& flux, const FPL::Definition::Fonctions::Argument& argument);

        Types::Type type;
        std::string name;
        Values::Value value;
    };

    class Fonction {
    private:
        std::string name;
        Values::Value returnValue;
        std::unordered_map<std::string, Argument> arguments;
        std::vector<FPL::Essential::Tokenizer::Token> tokensInFunction;

    public:
        Fonction();
        Fonction(std::string const& n, Values::Value const& v, std::vector<FPL::Essential::Tokenizer::Token> const& tokens);

        std::string getName();
        Values::Value getReturnValue();
        std::unordered_map<std::string, Argument> getArguments();
        std::vector<FPL::Essential::Tokenizer::Token> getTokensFunction();

        void setName(const std::string &n);
        void setReturnValue(FPL::Definition::Values::Value v);
        void setTokens(std::vector<FPL::Essential::Tokenizer::Token> const& tokens);
        bool isArgument(const std::string& a);
        std::optional<Argument> getArgument(const std::string& a);
        void addArgument(Argument arg);
        void removeArgument(FPL::Definition::Fonctions::Argument keyToRemove);
        int getArgumentsSize();
        void updateValueArgument(const std::string &argName, Values::Value const &argValue);
    };
}