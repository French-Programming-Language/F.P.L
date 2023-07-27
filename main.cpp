#include <iostream>
#include <fstream>

#include "src/Essentials/Tokenizer/Tokenizer.h"
#include "src/Essentials/Parser/Parser.h"

using namespace FPL;
using namespace FPL::Essential;
using namespace FPL::Essential::Tokenizer;

int main(int argc, char** argv) {
    std::string pos_FileName;
    if (argc == 2) {
        pos_FileName = argv[1];
    } else {
        std::cout << "Fichier : ";
        std::cin >> pos_FileName;
        std::cout << std::endl;
    }

    std::ifstream fichier_fpl {pos_FileName};
    if (!fichier_fpl) {
        std::cerr << "Fichier introuvable !" << std::endl;
        return -1;
    }

    std::string contentFile((std::istreambuf_iterator<char>(fichier_fpl)), (std::istreambuf_iterator<char>()));

    auto const TokenList = TokenBuilder::CodeToTokens(contentFile);

    FPL::Essential::Parser::Parser::main(TokenList);

    return 0;
}