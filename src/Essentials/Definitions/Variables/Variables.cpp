#include "Variables.h"

namespace FPL::Definition::Variables {
    std::ostream &operator<<(std::ostream &flux, const Variable &var) {
        flux << "(Variable:" << var.name << ", type: " << FPL::Definition::Types::Types_STR[var.type] << ", value: " << var.value << ", global: " << var.global << ")";
        return flux;
    }

    Variable::Variable() = default;

    Variable::Variable(const std::string& n, const std::string& v, Type t) {
        this->setName(n);
        this->setValue(v);
        this->setType(t);
    }

    void Variable::setName(std::string_view n) {
        this->name = n;
    }

    void Variable::setValue(std::string_view v) {
        this->value = v;
    }

    void Variable::setType(Type t) {
        this->type = t;
    }

    void Variable::setGlobal(bool b) {
        this->global = b;
    }

    void Variable::setMutable(bool b) {
        this->mut = b;
    }

    std::string Variable::getName() const {
        return this->name;
    }

    std::string Variable::getValue() const {
        return this->value;
    }

    Type Variable::getType() const {
        return this->type;
    }

    bool Variable::isGlobal() const {
        return this->global;
    }

    bool Variable::isMutable() const {
        return this->mut;
    }

    bool Variable::isArgument() const {
        return this->isargument;
    }

    void Variable::setIsArgument(bool a) {
        this->isargument = a;
    }
}

