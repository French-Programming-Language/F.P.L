#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <cctype>
#include <algorithm>

namespace FPL::Tokenizer {

        enum TokenTypes {
            ESPACE_VIDE,
            IDENTIFIANT,
            ENTIER,
            DECIMAL,
            PEUTETRE_DECIMAL,
            CHAINE_LITTERAL,
            OPERATEUR,
            STRING_ESCAPE_SEQUENCE,
            PEUTETRE_COMMENT,
            COMMENT
        };

        // Une copie sera faite au max, constexpr permet de mettre à disponible dès la compilation
        inline constexpr const char *sAllTokenTypes[] = {
                "ESPACE_VIDE",
                "IDENTIFIANT",
                "ENTIER",
                "DECIMAL",
                "PEUTETRE_DECIMAL",
                "CHAINE_LITTERAL",
                "OPERATEUR",
                "STRING_ESCAPE_SEQUENCE",
                "PEUTETRE_COMMENT",
                "COMMENT"
        };

        class Token {
        public:
            enum TokenTypes TokenType = ESPACE_VIDE;
            std::string TokenText;
            size_t TokenLineNumber {0};

            friend std::ostream& operator<<(std::ostream& flux, Token const& token);
        };

        class TokenBuilder {
        public:
            static std::vector<Token> ParseToken(const std::string& contentFile);

            static void ParseEndToken(Token& token, std::vector<Token>& tokens);
        };
    }