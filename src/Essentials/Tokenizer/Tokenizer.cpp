#include "Tokenizer.h"

namespace FPL::Essential::Tokenizer {
    std::ostream &operator<<(std::ostream &flux, const Token &token) {
        flux << "(Token: " << token.content << ", line: " << token.lineNumber << ", type: " << Types_STR[token.type] << ")";
        return flux;
    }

    std::vector<Token> TokenBuilder::CodeToTokens(std::string_view code) {
        std::vector<Token> tokenList;
        Token currentToken;

        for (auto const& element : code) {
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
                    if (currentToken.type == WHITESPACE) {
                        currentToken.type = INT;
                        currentToken.content.append(1,element);
                    } else if (currentToken.type == POSSIBLE_DOUBLE) {
                        currentToken.type = DOUBLE;
                        currentToken.content.append(1,element);
                    } else if (currentToken.type == IDENTIFIANT) {
                        ConcludeToken(currentToken, tokenList);
                        currentToken.type = INT;
                        currentToken.content.append(1,element);
                    } else {
                        currentToken.content.append(1,element);
                    }
                    break;

                case '.':
                    if (currentToken.type == INT) {
                        currentToken.type = POSSIBLE_DOUBLE;
                        currentToken.content.append(1,element);
                    } else if (currentToken.type == WHITESPACE) {
                        ConcludeToken(currentToken, tokenList);
                        currentToken.type = OPERATOR;
                        currentToken.content.append(1,element);
                        ConcludeToken(currentToken, tokenList);
                    } else {
                        currentToken.content.append(1,element);
                    }
                    break;

                case '{':
                case '}':
                case '(':
                case ')':
                case ',':
                case ';':
                case ':':
                case '*':
                case '/':
                case '+':
                case '-':
                case '=':
                case '>':
                case '[':
                case ']':
                case '<':
                    if (currentToken.type != POSSIBLE_STRING) {
                        ConcludeToken(currentToken, tokenList);
                        currentToken.type = OPERATOR;
                        currentToken.content.append(1,element);
                        ConcludeToken(currentToken, tokenList);
                    } else {
                        currentToken.content.append(1,element);
                    }
                    break;

                case '"':
                    if (currentToken.type == WHITESPACE) {
                        currentToken.type = POSSIBLE_STRING;
                        currentToken.content.append(1,element);
                    } else if (currentToken.type == POSSIBLE_STRING) {
                        currentToken.type = STRING;
                        currentToken.content.append(1,element);
                        ConcludeToken(currentToken, tokenList);
                    }
                    break;

                case '\n':
                    ConcludeToken(currentToken, tokenList);
                    currentToken.lineNumber += 1;
                    break;

                case ' ':
                    currentToken.content.append(1,element);
                    if (currentToken.type != POSSIBLE_STRING) {
                        ConcludeToken(currentToken, tokenList);
                    }
                    break;


                default:
                    if (currentToken.type == WHITESPACE || currentToken.type == INT || currentToken.type == DOUBLE) {
                        ConcludeToken(currentToken, tokenList);
                        currentToken.type = IDENTIFIANT;
                        currentToken.content.append(1,element);
                    } else {
                        currentToken.content.append(1,element);
                    }
            }
        }

        ConcludeToken(currentToken, tokenList);
        return tokenList;
    }

    void TokenBuilder::ConcludeToken(Token& token, std::vector<Token>& tokenList) {
        if (token.type != WHITESPACE) {
            tokenList.push_back(token);
        }

        token.type = WHITESPACE;
        token.content.erase();
    }
}