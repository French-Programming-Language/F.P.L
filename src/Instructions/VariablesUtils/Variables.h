#pragma once

#include <iostream>
#include <vector>

#include "../../Essentials/Tokenizer/Tokenizer.h"
#include "../../Essentials/Data/Data.h"
#include "../../Essentials/Expecter/Expecter.h"
#include "../../Essentials/Definitions/Variables/Variables.h"
#include "../../Essentials/ErrorsManager/ErrorsManager.h"
#include "../../Utils/stringTo.h"

#include "../../Essentials/Definitions/Fonctions/Fonctions.h"

using namespace FPL::Definition;

namespace FPL::Instruction::VariablesUtils {
    Variable defineVariable(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, std::optional<Fonctions::Fonction> fonction);
    Variable defineVariable_Paquet(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, std::string paquetName, std::optional<Fonctions::Fonction> fonction);
}