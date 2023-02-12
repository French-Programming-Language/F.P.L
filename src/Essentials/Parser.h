#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "Tokenizer.h"
#include "Utils/Expecter.h"
#include "Utils/ErrorsCodeManagement.h"
#include "Utils/Vectors.h"
#include "MathUtils/Converts.h"

#include "Definitions/Variables.h"
#include "Definitions/Fonction.h"

#include "../Instructions/Prints.h"
#include "../Instructions/Inputs.h"

#include "MathUtils/MathParser/MathParser.h"

namespace FPL::Parser {
    class Parser {
    public:
        static void ParserCode(std::vector<FPL::Tokenizer::Token>& Tokens);


    private:
        static Data::Data ParserCode_Func(std::vector<FPL::Tokenizer::Token>& Tokens, std::optional<FPL::FonctionDef>& fonction);
        static bool ManagerInstruction(FPL::Data::Data &data, std::optional<FPL::FonctionDef> fonction);

        static void PrintInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef>& fonction);
        static void VariableInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef>& fonction);
        static void ChangerInstruction(FPL::Data::Data& data);
        static void InputInstruction(FPL::Data::Data& data);
        static void MathInstruction(FPL::Data::Data& data);
        static void ConversionInstruction(FPL::Data::Data& data);

        static void ImporterInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef> fonction);
        static Data::Data ParserCode_Import(std::vector<FPL::Tokenizer::Token>& Tokens, std::optional<FPL::FonctionDef>& fonction);

        static void DefinirInstruction(FPL::Data::Data& data);
        static void AppelerInstruction(FPL::Data::Data& data);
        static void RenvoyerInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef> fonction);
    };
}