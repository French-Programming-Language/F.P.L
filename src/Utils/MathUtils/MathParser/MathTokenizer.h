#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace MathParser {
    enum AllTokenTypes {
        WHITESPACE,
        INT,
        DOUBLE,
        MAYBE_DOUBLE,
        OPERATOR
    };

    class Token {
    public:
        enum AllTokenTypes TokenType;
        std::string TokenText;

        friend bool operator==(Token const& a, Token const& b);
        friend double operator+(Token const& a, Token const& b);
        friend double operator-(Token const& a, Token const& b);
        friend double operator*(Token const& a, Token const& b);
        friend double operator/(Token const& a, Token const& b);
    };

    class TokenBuilding {
    public:
        static std::vector<Token> ParserTokens(const std::string& content);

        static void endToken(Token &token, std::vector<Token> &tokens);
    };
}