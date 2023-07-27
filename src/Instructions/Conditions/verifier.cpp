#include "verifier.h"


namespace FPL::Instruction::Verifier {
    void verifVariable(
            std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken,
            FPL::Essential::Data::Data &data,
            std::string var_name, std::optional<Fonctions::Fonction> fonction, std::optional<std::string> paquet)
            {
        Variable var = data.getVariable(var_name).value();

        if (ExpectOperator(currentToken, "{").has_value()) {
            int totalInstructionBeforeEnd = 0;
            int totalCasInVerifier = 0;

            while (true) {
                auto cas_title = ExpectIdentifiant(currentToken);
                if (cas_title.has_value() && cas_title->content == "cas") {
                    std::vector<std::string> caseBloc_verifier;

                    auto value_to_compare = ExpectValue(currentToken);
                    if (!value_to_compare.has_value()) {
                        forgotValue(currentToken);
                    }

                    if (var.getType() != value_to_compare->type) {
                        differentTypes(currentToken);
                    }

                    if (!ExpectOperator(currentToken, ":").has_value()) {
                        VERIFIER_CAS_openCode(currentToken);
                    }

                    while (true) {
                        if (currentToken->content == "verifier") {
                            totalInstructionBeforeEnd += 1;
                        }
                        else if (currentToken->content == "cas" || currentToken->content == "cas ") {
                            totalCasInVerifier += 1;
                        }

                        caseBloc_verifier.push_back(currentToken->content);
                        ++currentToken;

                        if (ExpectOperator(currentToken, ",").has_value()) {
                            if (totalCasInVerifier > 0) {
                                caseBloc_verifier.emplace_back(",");
                                totalCasInVerifier -= 1;
                            } else {
                                break;
                            }
                        }
                    }

                    if (var.getValue() == value_to_compare->content) {
                        auto const TokenList = TokenBuilder::CodeToTokens(FPL::Utils::StringVectorToString(caseBloc_verifier));
                        auto new_data = Parser::Parser::executeCode(TokenList, data, paquet, fonction);
                        for (auto const& v : new_data.Variables) {
                            if (v.second.isGlobal()) {
                                data.pushVariable(v.second);
                            }
                        }
                    }
                } else {
                    VERIFIER_CAS_title(currentToken);
                }

                if (ExpectOperator(currentToken, "}").has_value()) {
                    if (totalInstructionBeforeEnd > 0) {
                        totalInstructionBeforeEnd -= 1;
                    } else {
                        break;
                    }
                }
            }
        }
        else {
            forgotToOpenCode(currentToken);
        }
    }

    void verifArgument(
            std::vector<FPL::Essential::Tokenizer::Token>::iterator &currentToken,
            FPL::Essential::Data::Data &data,
            std::string var_name, std::optional<Fonctions::Fonction> fonction, std::optional<std::string> paquet)
    {
        auto argument = fonction->getArgument(var_name);

        if (ExpectOperator(currentToken, "{").has_value()) {
            int totalInstructionBeforeEnd = 0;
            int totalCasInVerifier = 0;

            while (true) {
                auto cas_title = ExpectIdentifiant(currentToken);
                if (cas_title.has_value() && cas_title->content == "cas") {
                    std::vector<std::string> caseBloc_verifier;

                    auto value_to_compare = ExpectValue(currentToken);
                    if (!value_to_compare.has_value()) {
                        forgotValue(currentToken);
                    }

                    if (argument->getType() != value_to_compare->type) {
                        differentTypes(currentToken);
                    }

                    if (!ExpectOperator(currentToken, ":").has_value()) {
                        VERIFIER_CAS_openCode(currentToken);
                    }

                    while (true) {
                        if (currentToken->content == "verifier") {
                            totalInstructionBeforeEnd += 1;
                        }
                        else if (currentToken->content == "cas" || currentToken->content == "cas ") {
                            totalCasInVerifier += 1;
                        }

                        caseBloc_verifier.push_back(currentToken->content);
                        ++currentToken;

                        if (ExpectOperator(currentToken, ",").has_value()) {
                            if (totalCasInVerifier > 0) {
                                caseBloc_verifier.emplace_back(",");
                                totalCasInVerifier -= 1;
                            } else {
                                break;
                            }
                        }
                    }

                    if (argument->getValue().content == value_to_compare->content) {
                        auto const TokenList = TokenBuilder::CodeToTokens(FPL::Utils::StringVectorToString(caseBloc_verifier));
                        auto new_data = Parser::Parser::executeCode(TokenList, data, paquet, fonction);
                        for (auto const& v : new_data.Variables) {
                            if (v.second.isGlobal()) {
                                data.pushVariable(v.second);
                            }
                        }
                    }
                } else {
                    VERIFIER_CAS_title(currentToken);
                }

                if (ExpectOperator(currentToken, "}").has_value()) {
                    if (totalInstructionBeforeEnd > 0) {
                        totalInstructionBeforeEnd -= 1;
                    } else {
                        break;
                    }
                }
            }
        }
        else {
            forgotToOpenCode(currentToken);
        }
    }
}