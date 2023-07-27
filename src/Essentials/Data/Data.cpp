#include "Data.h"

namespace FPL::Essential::Data {

    std::optional<Variable> Data::getVariable(const std::string& name) {
        if (variableExist(name)) {
            return Variables[name];
        }
        return std::nullopt;
    }

    bool Data::variableExist(const std::string& name) {
        if (Variables.contains(name)) {
            return true;
        }
        return false;
    }

    bool Data::variableExist(Variable v) {
        if (Variables.contains(v.getName())) {
            return true;
        }
        return false;
    }

    void Data::pushVariable(Variable var) {
        Variables[var.getName()] = var;
    }

    void Data::updateVariableValue(Variable var, const std::string &v) {
        var.setValue(v);
        Variables[var.getName()] = var;
    }

    void Data::deleteVariableFromMap(Variable keyToRemove) {
        auto it = Variables.find(keyToRemove.getName());
        if (it != Variables.end()) {
            Variables.erase(it);
        }
    }

    void Data::pushFonction(FPL::Definition::Fonctions::Fonction f) {
        Fonctions[f.getName()] = f;
    }

    std::optional<FPL::Definition::Fonctions::Fonction> Data::getFonction(const std::string &name) {
        if (isFonction(name)) {
            return Fonctions[name];
        }
        return std::nullopt;
    }

    bool Data::isFonction(const std::string &name) {
        if (Fonctions.contains(name)) {
            return true;
        }
        return false;
    }

    std::optional<FPL::Definition::Fonctions::Argument>
    Data::getFonctionArgument(const std::string &functionName, const std::string &argName) {
        if (isFonctionArgument(functionName, argName)) {
            auto f = this->getFonction(functionName);
            if (f->getArguments().contains(argName)) {
                return f->getArgument(argName);
            }
        }
        return std::nullopt;
    }

    bool Data::isFonctionArgument(const std::string &functionName, const std::string &argName) {
        if (isFonction(functionName)) {
            auto f = this->getFonction(functionName);
            if (f->getArguments().contains(argName)) {
                return true;
            }
        }
        return false;
    }
}