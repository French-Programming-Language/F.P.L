#pragma once

#include <iostream>
#include <vector>

#include "../../Essentials/Tokenizer/Tokenizer.h"
#include "../../Essentials/Data/Data.h"
#include "../../Essentials/Expecter/Expecter.h"
#include "../../Utils/stringTo.h"

namespace FPL::Instruction::Saisir {
    void attributeTypeAndValue(Variable& var, FPL::Definition::Types::Type& var_type, const std::string& v);
    void giveValueAndType(Variable& var, FPL::Definition::Types::Type& var_type, std::string& get_answer_user);
}