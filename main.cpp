#include "src/TokenBuilding.h"
#include "src/Parser.h"
#include "src/FonctionDefinition.h"
#include <iostream>
#include <string>
#include <optional>
#include <fstream>

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
    std::string f_content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    FPL::TokenBuilding t;
    std::vector<FPL::Token> tokens = t.parseToken(f_content);
    FPL::Parser parser;
    parser.parse(tokens, (std::optional<FPL::FonctionDefinition> &) std::nullopt);
    return 0;
}