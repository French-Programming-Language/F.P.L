#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <string_view>
#include <optional>
#include <map>

#include "../Tokenizer/Tokenizer.h"
#include "../Definitions/Value/Value.h"
#include "../Definitions/Types/Types.h"

using namespace FPL::Essential;
using namespace FPL::Essential::Tokenizer;

std::optional<Token> ExpectIdentifiant(std::vector<Token>::iterator &current);
std::optional<Token> ExpectOperator(std::vector<Token>::iterator &current, std::string_view o = "");
std::optional<std::string> ExpecterConditionalOperator(std::vector<Token>::iterator &current);
std::optional<FPL::Definition::Values::Value> ExpectValue(std::vector<Token>::iterator &current);
std::optional<FPL::Definition::Types::Type> ExpectType(std::vector<Token>::iterator &current);
bool ExpectEqualOperator(std::vector<Token>::iterator &current);