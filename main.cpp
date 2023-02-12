#include <iostream>

#include "src/Essentials/Tokenizer.h"
#include "src/Essentials/Parser.h"

using namespace FPL;

int main(int argc, char** argv) {
    std::string fileName;
    if (argc == 2) {
        fileName = argv[1];
    } else {
        std::cout << "Fichier : ";
        std::cin >> fileName;
        std::cout << std::endl;
    }
    std::ifstream file { fileName};
    if (!file) {
        std::cerr << "Donnez le nom correct du fichier." << std::endl;
        return 1;
    }
    std::string FileCode((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    std::vector<Tokenizer::Token> FileCode_Tokens = FPL::Tokenizer::TokenBuilder::ParseToken(FileCode);
    FPL::Parser::Parser::ParserCode(FileCode_Tokens);

    return 0;
}