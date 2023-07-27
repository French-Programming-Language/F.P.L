#include "Fonctions.h"

std::string FPL::Definition::Fonctions::Fonction::getName() {
    return this->name;
}

FPL::Definition::Values::Value FPL::Definition::Fonctions::Fonction::getReturnValue() {
    return this->returnValue;
}

std::unordered_map<std::string, FPL::Definition::Fonctions::Argument> FPL::Definition::Fonctions::Fonction::getArguments() {
    return this->arguments;
}

std::vector<FPL::Essential::Tokenizer::Token> FPL::Definition::Fonctions::Fonction::getTokensFunction() {
    return this->tokensInFunction;
}

void FPL::Definition::Fonctions::Fonction::setName(const std::string &n) {
    this->name = n;
}

void FPL::Definition::Fonctions::Fonction::setReturnValue(FPL::Definition::Values::Value v) {
    this->returnValue = v;
}

bool FPL::Definition::Fonctions::Fonction::isArgument(const std::string& a) {
    if (this->arguments.contains(a)) {
        return true;
    }
    return false;
}

std::optional<FPL::Definition::Fonctions::Argument> FPL::Definition::Fonctions::Fonction::getArgument(const std::string &a) {
    if (this->isArgument(a)) {
        return this->arguments[a];
    }
    return std::nullopt;
}

void FPL::Definition::Fonctions::Fonction::addArgument(FPL::Definition::Fonctions::Argument arg) {
    this->arguments[arg.getName()] = arg;
}

void FPL::Definition::Fonctions::Fonction::removeArgument(FPL::Definition::Fonctions::Argument keyToRemove) {
    auto it = this->getArguments().find(keyToRemove.getName());
    if (it != this->getArguments().end()) {
        this->getArguments().erase(it);
    }
}

FPL::Definition::Fonctions::Fonction::Fonction(const std::string &n, const FPL::Definition::Values::Value &v, const std::vector<FPL::Essential::Tokenizer::Token> &tokens) {
    this->setName(n);
    this->setReturnValue(v);
    this->setTokens(tokens);
}

void FPL::Definition::Fonctions::Fonction::setTokens(std::vector<FPL::Essential::Tokenizer::Token> const& tokens) {
    this->tokensInFunction = tokens;
}

int FPL::Definition::Fonctions::Fonction::getArgumentsSize() {
    return this->arguments.size();
}

void FPL::Definition::Fonctions::Fonction::updateValueArgument(const std::string &argName, Values::Value const &argValue) {
    if (isArgument(argName)) {
        this->arguments[argName].setValue(argValue);
    }
}

FPL::Definition::Fonctions::Fonction::Fonction() = default;

std::string FPL::Definition::Fonctions::Argument::getName() {
    return this->name;
}

FPL::Definition::Types::Type FPL::Definition::Fonctions::Argument::getType() {
    return this->type;
}

FPL::Definition::Values::Value FPL::Definition::Fonctions::Argument::getValue() {
    return this->value;
}

void FPL::Definition::Fonctions::Argument::setName(std::string const& n) {
    this->name = n;
}

void FPL::Definition::Fonctions::Argument::setType(const FPL::Definition::Types::Type &t) {
    this->type = t;
}

void FPL::Definition::Fonctions::Argument::setValue(const FPL::Definition::Values::Value &v) {
    this->value = v;
}

FPL::Definition::Fonctions::Argument::Argument(std::string const& n, FPL::Definition::Types::Type const& t, FPL::Definition::Values::Value const& v) {
    this->setName(n);
    this->setType(t);
    this->setValue(v);
}

std::ostream& FPL::Definition::Fonctions::operator<<(std::ostream& flux, const FPL::Definition::Fonctions::Argument& argument) {
    flux << "(ARG: " << argument.name << ", " << argument.value.content << ", " << Types::Types_STR[argument.type] << ")";
    return flux;
}


FPL::Definition::Fonctions::Argument::Argument() = default;
