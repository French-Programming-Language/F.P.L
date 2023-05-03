#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stack>
#include <fstream>

#include "Tokenizer.h"
#include "Utils/Expecter.h"
#include "Utils/ErrorsCodeManagement.h"
#include "Utils/Vectors.h"
#include "MathUtils/Converts.h"

#include "Definitions/Variables.h"
#include "Definitions/Fonction.h"
#include "Definitions/Paquet.h"

#include "../Instructions/Prints.h"
#include "../Instructions/Inputs.h"
#include "../Instructions/FunctionsUtils.h"
#include "../Instructions/TantQue_Loop.h"


#include "MathUtils/MathParser/MathParser.h"

namespace FPL::Parser {
    class Parser {
    public:
        static void ParserCode(std::vector<FPL::Tokenizer::Token>& Tokens);

        static Data::Data executeContentCode(std::vector<FPL::Tokenizer::Token>& Tokens, const std::optional<FPL::FonctionDef>& fonction, const std::optional<FPL::Paquet::Paquet>& paquet, FPL::Data::Data& universalData);

    private:
        static bool ManagerInstruction(FPL::Data::Data &data, std::optional<FPL::FonctionDef> fonction, const std::optional<FPL::Paquet::Paquet>& paquet);

        static void PrintInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef>& fonction);
        static void VariableInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef>& fonction, const std::optional<FPL::Paquet::Paquet>& paquet);
        static void ChangerInstruction(FPL::Data::Data& data);
        static void InputInstruction(FPL::Data::Data& data, std::optional<FPL::Paquet::Paquet> paquet);
        static void MathInstruction(FPL::Data::Data& data, std::optional<FPL::Paquet::Paquet> paquet);
        static void ConversionInstruction(FPL::Data::Data& data);

        static void ImporterInstruction(FPL::Data::Data& data, const std::optional<FPL::FonctionDef>& fonction);

        static void DefinirInstruction(FPL::Data::Data& data, std::optional<FPL::Paquet::Paquet> paquet);
        static void AppelerInstruction(FPL::Data::Data& data);
        static void RenvoyerInstruction(FPL::Data::Data& data, std::optional<FPL::FonctionDef> fonction);

        static void PaquetInstruction(FPL::Data::Data &data, const std::optional<FPL::FonctionDef>& fonction, std::optional<FPL::Paquet::Paquet> paquet);

        static void FichierInstruction(FPL::Data::Data &data, std::optional<FPL::Paquet::Paquet> paquet);

        static void TypeInstruction(FPL::Data::Data &data, std::optional<FPL::Paquet::Paquet> paquet);

        static void TantQueInstruction(FPL::Data::Data &data, std::optional<FPL::FonctionDef>& fonction);
    };
}