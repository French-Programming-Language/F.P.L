#include "Saisir.h"

namespace FPL::Instruction::Saisir {
    void attributeTypeAndValue(Variable& var, FPL::Definition::Types::Type var_type, const std::string& v) {
        var.setType(var_type);
        var.setValue(v);
    }

    void giveValueAndType(Variable& var, FPL::Definition::Types::Type& var_type, std::string& get_answer_user) {
        if (var_type == FPL::Definition::Types::Type::STRING) {
            attributeTypeAndValue(var, FPL::Definition::Types::Type::STRING, get_answer_user);
        } else if (var_type == FPL::Definition::Types::Type::INT) {
            auto int_v = FPL::Utils::stringToInt(get_answer_user);
            if (int_v.has_value()) {
                attributeTypeAndValue(var, FPL::Definition::Types::Type::INT, get_answer_user);
            } else {
                attributeTypeAndValue(var, FPL::Definition::Types::Type::STRING, "vide");
            }
        } else if (var_type == FPL::Definition::Types::Type::DOUBLE) {
            auto double_v = FPL::Utils::stringToDouble(get_answer_user);
            if (double_v.has_value()) {
                attributeTypeAndValue(var, FPL::Definition::Types::Type::DOUBLE, get_answer_user);
            } else {
                attributeTypeAndValue(var, FPL::Definition::Types::Type::STRING, "vide");
            }
        } else if (var_type == FPL::Definition::Types::Type::BOOL) {
            attributeTypeAndValue(var, FPL::Definition::Types::Type::BOOL, get_answer_user);
        }
    }
}