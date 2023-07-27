#pragma once

#include <iostream>
#include <vector>

#include "../../Essentials/Tokenizer/Tokenizer.h"
#include "../../Essentials/Data/Data.h"
#include "../../Essentials/Expecter/Expecter.h"
#include "../../Essentials/ErrorsManager/ErrorsManager.h"
#include "../../Essentials/Definitions/Fonctions/Fonctions.h"

#include "../../Essentials/Parser/Parser.h"

#include "../../Utils/VectorsTo.h"

using namespace FPL::Definition;

namespace FPL::Instruction::Verifier {
    void verifVariable(
            std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken,
            FPL::Essential::Data::Data &data,
            std::string var_name, std::optional<Fonctions::Fonction> fonction, std::optional<std::string> paquet) ;

    void verifArgument(
            std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken,
            FPL::Essential::Data::Data &data,
            std::string var_name, std::optional<Fonctions::Fonction> fonction, std::optional<std::string> paquet) ;
}