#pragma once

#include <iostream>
#include <vector>

#include "../../Essentials/Tokenizer/Tokenizer.h"
#include "../../Essentials/Data/Data.h"
#include "../../Essentials/Expecter/Expecter.h"

#include "../../Essentials/ErrorsManager/ErrorsManager.h"

#include "../../Essentials/Definitions/Fonctions/Fonctions.h"

using namespace FPL::Definition;

namespace FPL::Instruction::Envoyer {
    void getInformation(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, bool &pass, std::optional<Fonctions::Fonction> fonction);
    void getInformation(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, std::optional<Fonctions::Fonction> fonction);
}