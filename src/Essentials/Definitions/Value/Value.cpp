#include "Value.h"

FPL::Definition::Values::Value::Value() = default;

FPL::Definition::Values::Value::Value(FPL::Definition::Types::Type type, std::string content) {
    this->type = type;
    this->content = content;
}
