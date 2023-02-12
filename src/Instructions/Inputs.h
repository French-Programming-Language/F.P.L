#pragma once

#include <iostream>
#include <string>

#include "../Essentials/Types.h"
#include "../Essentials/Utils/Data.h"
#include "../Essentials/Utils/ErrorsCodeManagement.h"

namespace FPL::Instruction::Inputs {
    std::string returnInputFinalValue(FPL::Types::BUILTIN_TYPE& type, FPL::Data::Data& data);
}