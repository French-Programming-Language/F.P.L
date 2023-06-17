#pragma once

#include <iostream>
#include "../Essentials/Utils/Data.h"
#include "../Essentials/Parser.h"
#include "../Essentials/Definitions/Variables.h"
#include "../Essentials/Definitions//Fonction.h"
#include "../Essentials/Utils/ErrorsCodeManagement.h"
#include "../Essentials/Utils/Vectors.h"


namespace FPL::Instruction::TantQue {
    // Operator: <
    void increment_int_operatorLowerUpper(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd);
    void increment_double_operatorLowerUpper(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd);
    void decrement_int_operatorLowerUpper(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd);
    void decrement_double_operatorLowerUpper(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd);

    // Operator: >
    void increment_int_operatorUpperLower(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd);
    void increment_double_operatorUpperLower(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd);
    void decrement_int_operatorUpperLower(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd);
    void decrement_double_operatorUpperLower(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd);
}