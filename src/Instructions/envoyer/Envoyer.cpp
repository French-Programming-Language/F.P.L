#include "Envoyer.h"

namespace FPL::Instruction::Envoyer {
    void getInformation(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, bool &pass, std::optional<Fonctions::Fonction> fonction) {
        auto contenu = ExpectValue(currentToken);
        if (contenu.has_value()) {
            std::cout << contenu->content;
            pass = true;
        } else {
            auto identifiant = ExpectIdentifiant(currentToken);
            if (identifiant.has_value() && data.variableExist(identifiant->content)) {
                std::cout << data.getVariable(identifiant->content)->getValue();
                pass = true;
            }
        }
    }

    void getInformation(std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken, FPL::Essential::Data::Data &data, std::optional<Fonctions::Fonction> fonction) {
        auto contenu = ExpectValue(currentToken);
        if (contenu.has_value()) {
            std::cout << contenu->content;
        } else {
            auto identifiant = ExpectIdentifiant(currentToken);
            if (identifiant.has_value() && data.variableExist(identifiant->content)) {
                std::cout << data.getVariable(identifiant->content)->getValue();
            }
        }
    }
}