#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include <iterator>
#include <optional>
#include <map>
#include <unordered_map>
#include <utility>

#include "../Tokenizer/Tokenizer.h"
#include "../Data/Data.h"
#include "../Expecter/Expecter.h"
#include "../ErrorsManager/ErrorsManager.h"

#include "../Definitions/Value/Value.h"
#include "../Definitions/Variables/Variables.h"
#include "../Definitions/Fonctions/Fonctions.h"

#include "../../Instructions/envoyer/Envoyer.h"
#include "../../Instructions/saisir/Saisir.h"
#include "../../Instructions/VariablesUtils/Variables.h"
#include "../../Instructions/Conditions/verifier.h"

#include "../../Utils/stringTo.h"
#include "../../Utils/VectorsTo.h"

#include "../../Utils/MathUtils/MathParser/MathTokenizer.h"
#include "../../Utils/MathUtils/MathParser/MathParser.h"

using namespace FPL::Definition;
using namespace FPL::Essential::Tokenizer;
using namespace FPL::Essential::Data;

namespace FPL::Essential::Parser {
    class Parser {
    public:
        static void main(std::vector<Token> tokenList);
        static Data::Data executeCode(std::vector<Token> tokenList, std::optional<Data::Data> old_data, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction);
        static bool managerInstructions( std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);

        // Basics:
        static void ENVOYER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void VARIABLE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void CHANGER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void SAISIR_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::optional<std::string> paquet, std::optional<Fonctions::Fonction> fonction);
        static void FICHIER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void CONSTANTE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void GLOBALE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void RETIRER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void IMPORTER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction);
        static void CONVERTIR_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void VERIFIER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction);
        static void TANT_QUE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction);
        static void PAQUET_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList, std::optional<std::string> paquet, std::optional<Fonctions::Fonction> fonction);
        static void DEFINIR_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void APPELER_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token>& tokenList, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
        static void MATH_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token>& tokenList, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction);
    };
}