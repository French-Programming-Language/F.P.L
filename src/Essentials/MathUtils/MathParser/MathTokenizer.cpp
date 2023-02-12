#include "MathTokenizer.h"

namespace MathParser {
    std::vector<Token> TokenBuilding::ParserTokens(const std::string &content) {
        std::vector<Token> tokens;
        Token currentToken;

        for (auto const& element : content) {
            switch (element) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (currentToken.TokenType == WHITESPACE) {
                        currentToken.TokenType = INT;
                        currentToken.TokenText.append(1, element);
                    } else if (currentToken.TokenType == MAYBE_DOUBLE) {
                        currentToken.TokenType = DOUBLE;
                        currentToken.TokenText.append(1, element);
                    } else {
                        currentToken.TokenText.append(1, element);
                    }
                    break;

                case '.':
                    if (currentToken.TokenType == WHITESPACE) {
                        currentToken.TokenType = MAYBE_DOUBLE;
                        currentToken.TokenText.append(1, element);
                    } else if (currentToken.TokenType == INT) {
                        currentToken.TokenType = DOUBLE;
                        currentToken.TokenText.append(1, element);
                    } else {
                        TokenBuilding::endToken( currentToken, tokens);
                        currentToken.TokenType = OPERATOR;
                        currentToken.TokenText.append(1, element);
                        TokenBuilding::endToken(currentToken, tokens);
                    }
                    break;

                case '+':
                case '-':
                case '/':
                case '*':
                    TokenBuilding::endToken(currentToken, tokens);
                    currentToken.TokenType = OPERATOR;
                    currentToken.TokenText.append(1, element);
                    TokenBuilding::endToken(currentToken, tokens);
                    break;

                default:
                    break;
            }
        }
        TokenBuilding::endToken(currentToken, tokens);
        return tokens;
    }

    void TokenBuilding::endToken(Token &token, std::vector<Token> &tokens) {
        if (token.TokenType != WHITESPACE) {
            tokens.push_back(token);
        }

        if (token.TokenType == MAYBE_DOUBLE)
        {
            if (token.TokenText == ".") {
                token.TokenType = OPERATOR;
            } else {
                token.TokenType = MAYBE_DOUBLE;
            }
        }

        token.TokenType = WHITESPACE;
        token.TokenText.erase();
    }

    bool operator==(Token const& a, Token const& b)  {
        return a.TokenText == b.TokenText;
    }

    double operator+(Token const& a, Token const& b)  {
        try {
            double v = std::stod(a.TokenText);
            double v2 = std::stod(b.TokenText);
            return v + v2;
        }
        catch (std::invalid_argument const& ex) {
            std::cout << "It can not be a double/int value !" << " Final error: " << ex.what() << std::endl;
        }
        return 0;
    }

    double operator-(Token const& a, Token const& b)  {
        try {
            double v = std::stod(a.TokenText);
            double v2 = std::stod(b.TokenText);
            return v - v2;
        }
        catch (std::invalid_argument const& ex) {
            std::cout << "It can not be a double/int value !" << " Final error: " << ex.what() << std::endl;
        }
        return 0;
    }

    double operator*(Token const& a, Token const& b)  {
        try {
            double v = std::stod(a.TokenText);
            double v2 = std::stod(b.TokenText);
            return v * v2;
        }
        catch (std::invalid_argument const& ex) {
            std::cout << "It can not be a double/int value !" << " Final error: " << ex.what() << std::endl;
        }
        return 0;
    }

    double operator/(Token const& a, Token const& b)  {
        try {
            double v = std::stod(a.TokenText);
            double v2 = std::stod(b.TokenText);
            return v / v2;
        }
        catch (std::invalid_argument const& ex) {
            std::cout << "It can not be a double/int value !" << " Final error: " << ex.what() << std::endl;
        }
        return 0;
    }
}