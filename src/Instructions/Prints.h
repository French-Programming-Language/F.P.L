#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "../Essentials/Utils/Data.h"
#include "../Essentials/Utils/ErrorsCodeManagement.h"
#include "../Essentials/Utils/Expecter.h"

#include "../Essentials/Definitions/Fonction.h"
#include "../Essentials/Definitions/Variables.h"

#include "../Essentials/MathUtils/Converts.h"

namespace FPL::Instruction::Prints {
    void printWithOperatorCondition_INT(std::string_view currOP, int a, int b);
    void printWithOperatorCondition_DOUBLE(std::string_view currOP, double a, double b);
    void managementPrint_VARIABLE(FPL::Data::Data &data, FPL::VariableDef &var);
    void managementPrint_ARGUMENT(FPL::Data::Data &data, std::optional<FPL::FonctionArgumentDef> &arg);
}