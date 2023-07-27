#include "Parser.h"

namespace FPL::Essential::Parser {

    void Parser::main(std::vector<Token> tokenList) {
        Data::Data main_data;
        auto currentToken = tokenList.begin();

        while (currentToken != tokenList.end()) {
            if (!managerInstructions(currentToken, main_data, tokenList, std::nullopt, std::nullopt)) {
                std::cerr << "Inconnu: " << currentToken->content << ", ligne " << currentToken->lineNumber << "." << std::endl;
                ++currentToken;
                continue;
            }
        }
    }

    Data::Data Parser::executeCode(std::vector<Token> tokenList, std::optional<Data::Data> old_data, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction) {
        Data::Data data;

        if (old_data.has_value()) {
            for (auto const& v : old_data->Variables) {
                data.pushVariable(v.second);
            }
        }

        auto currentToken = tokenList.begin();

        while (currentToken != tokenList.end()) {
            if (!managerInstructions(currentToken, data, tokenList, paquet, fonction)) {
                std::cerr << "Inconnu: " << currentToken->content << ", ligne " << currentToken->lineNumber << "." << std::endl;
                ++currentToken;
                continue;
            }
        }

        return data;
    }

    bool Parser::managerInstructions(std::vector<Token>::iterator& currentToken, Data::Data &data, std::vector<Token> tokenList, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto instruction = ExpectIdentifiant(currentToken);
        if (instruction.has_value()) {
            if (instruction->content == "envoyer") {
                ENVOYER_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "variable") {
                VARIABLE_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "changer") {
                CHANGER_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "saisir") {
                SAISIR_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "fichier") {
                FICHIER_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "constante") {
                CONSTANTE_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "globale") {
                GLOBALE_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "retirer") {
                RETIRER_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "importer") {
                IMPORTER_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "convertir") {
                CONVERTIR_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "verifier") {
                VERIFIER_Instruction(currentToken, data, paquet, fonction);
                return true;
            } else if (instruction->content == "tantque") {
                TANT_QUE_Instruction(currentToken, data, std::move(tokenList), paquet, fonction);
                return true;
            } else if (instruction->content == "paquet") {
                PAQUET_Instruction(currentToken, data, tokenList, paquet, fonction);
                return true;
            } else if (instruction->content == "definir") {
                DEFINIR_Instruction(currentToken, data, tokenList, paquet, fonction);
                return true;
            } else if (instruction->content == "appeler") {
                APPELER_Instruction(currentToken, data, tokenList, paquet, fonction);
                return true;
            } else if (instruction->content == "math") {
                MATH_Instruction(currentToken, data, tokenList, paquet, fonction);
                return true;
            }
        }
        return false;
    }

    void Parser::ENVOYER_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        bool pass = false;

        FPL::Instruction::Envoyer::getInformation(currentToken, data, pass, fonction);

        if (!pass) {
            bool pass2 = false;

            if (ExpectOperator(currentToken,"[").has_value()) {
                while (!ExpectOperator(currentToken, "]").has_value()) {
                    FPL::Instruction::Envoyer::getInformation(currentToken, data, fonction);
                }
                pass2 = true;
            }

            if (!pass2) {
                forgotValue(currentToken);
            }
        }

        std::cout << std::endl;
    }

    void Parser::VARIABLE_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction) {
        if (paquet.has_value()) {
            Variable var = FPL::Instruction::VariablesUtils::defineVariable_Paquet(currentToken, data, paquet.value(), fonction);

            if (data.variableExist(var)) {
                VARIABLE_Instruction_Exist(currentToken);
            }

            data.pushVariable(var);
        } else {
            Variable var = FPL::Instruction::VariablesUtils::defineVariable(currentToken, data, fonction);

            if (data.variableExist(var)) {
                VARIABLE_Instruction_Exist(currentToken);
            }

            data.pushVariable(var);
        }
    }

    void Parser::CHANGER_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            CHANGER_Instruction_unknowVariable(currentToken);
        }

        if (!ExpectEqualOperator(currentToken)) {
            forgotEqualOperator(currentToken);
        }

        auto new_var_value = ExpectValue(currentToken);
        if (!new_var_value.has_value()) {
            forgotValue(currentToken);
        }

        if (!data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        auto var = data.getVariable(var_name->content);

        if (!var->isMutable()) {
            variable_no_mutable(currentToken);
        }

        if (new_var_value->type != var->getType()) {
            differentTypes(currentToken);
        }

        data.updateVariableValue(var.value(), new_var_value->content);
    }

    void Parser::SAISIR_Instruction( std::vector<Token>::iterator& currentToken, Data::Data& data, std::optional<std::string> paquet, std::optional<Fonctions::Fonction> fonction) {
        auto var_type = ExpectType(currentToken);
        if (!var_type.has_value()) {
            forgotType(currentToken);
        }

        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            forgotName(currentToken);
        }

        std::string varName = var_name->content;

        if (paquet.has_value()) {
            varName = paquet.value() + "." + var_name->content;
        }

        bool msg = false;

        if (ExpectEqualOperator(currentToken)) {
            msg = true;
        }

        auto message_to_output = ExpectValue(currentToken);
        if (message_to_output.has_value() && msg) {
            std::cout << message_to_output->content;
        } else if (msg && !message_to_output.has_value()) {
            auto possibleID = ExpectIdentifiant(currentToken);
            if (!possibleID.has_value()) {
                forgotValue(currentToken);
            }

            if (fonction.has_value() && fonction->isArgument(possibleID->content)) {
                std::cout << fonction->getArgument(possibleID->content)->getValue().content;
            } else if (data.variableExist(possibleID->content)) {
                std::cout << data.getVariable(possibleID->content)->getValue();
            }
        }

        if (data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        std::string get_answer_user;
        std::cin >> get_answer_user;
        std::cout << std::endl;

        Variable var;
        var.setName(varName);

        FPL::Instruction::Saisir::giveValueAndType(var, var_type.value(), get_answer_user);

        data.pushVariable(var);
    }

    void Parser::FICHIER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto instru = ExpectIdentifiant(currentToken);
        if (!instru.has_value()) {
            missingparameter(currentToken);
        }

        if (instru->content == "lire") {
            auto var_name = ExpectIdentifiant(currentToken);
            if (!var_name.has_value()) {
                forgotName(currentToken);
            }

            if (data.variableExist(var_name->content)) {
                VARIABLE_Instruction_Exist(currentToken);
            }

            auto file_name = ExpectValue(currentToken);
            if (file_name->type != FPL::Definition::Types::Type::STRING) {
                unknowfile(currentToken);
            }

            std::ifstream file {file_name->content};
            if (!file) {
                unknowfile(currentToken);
            }

            std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

            Variable var(var_name->content, content, FPL::Definition::Types::Type::STRING);
            data.pushVariable(var);
        } else if (instru->content == "ecrire") {
            auto file_name = ExpectValue(currentToken);
            if (file_name->type != FPL::Definition::Types::Type::STRING) {
                unknowfile(currentToken);
            }

            std::ofstream file {file_name->content};
            if (!file) {
                unknowfile(currentToken);
            }

            if (!ExpectEqualOperator(currentToken)) {
                forgotEqualOperator(currentToken);
            }

            auto contentToWrite = ExpectValue(currentToken);
            if (!contentToWrite.has_value()) {
                forgotValue(currentToken);
            }

            file << contentToWrite->content;
        } else {
            invalidparameter(currentToken);
        }
    }

    void Parser::CONSTANTE_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto possibleGlobal = ExpectIdentifiant(currentToken);
        bool global = false;
        if (possibleGlobal.has_value() && possibleGlobal->content == "globale") {
            global = true;
        } else if (possibleGlobal.has_value() && possibleGlobal->content != "globale"
          && possibleGlobal->content != "entier"
          && possibleGlobal->content != "decimal"
          && possibleGlobal->content != "texte"
          && possibleGlobal->content != "bool"
          && possibleGlobal->content != "booleen") { /* On exclut les types de F.P.L */
            invalidparameter(currentToken);
        } else {
            --currentToken; // Ca peut être un type donc on revient en arrière d'un token
        }

        if (paquet.has_value()) {
            Variable var = FPL::Instruction::VariablesUtils::defineVariable_Paquet(currentToken, data, paquet.value(), fonction);

            var.setMutable(false);
            if (global) {
                var.setGlobal(true);
            }

            if (data.variableExist(var)) {
                VARIABLE_Instruction_Exist(currentToken);
            }
            data.pushVariable(var);
        } else {
            Variable var = FPL::Instruction::VariablesUtils::defineVariable(currentToken, data, fonction);

            var.setMutable(false);
            if (global) {
                var.setGlobal(true);
            }

            if (data.variableExist(var)) {
                VARIABLE_Instruction_Exist(currentToken);
            }
            data.pushVariable(var);
        }
    }

    void Parser::GLOBALE_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto possibleConst = ExpectIdentifiant(currentToken);
        bool cons = false;
        if (possibleConst.has_value() && possibleConst->content == "constante") {
            cons = true;
        } else if (possibleConst.has_value() && possibleConst->content != "constante"
                   && possibleConst->content != "entier"
                   && possibleConst->content != "decimal"
                   && possibleConst->content != "texte"
                   && possibleConst->content != "bool"
                   && possibleConst->content != "booleen") { /* On exclut les types de F.P.L */
            invalidparameter(currentToken);
        } else {
            --currentToken; // Ca peut être un type donc on revient en arrière d'un token
        }

        if (paquet.has_value()) {
            Variable var = FPL::Instruction::VariablesUtils::defineVariable_Paquet(currentToken, data, paquet.value(), fonction);

            var.setGlobal(true);
            if (cons) {
                var.setMutable(false);
            }

            if (data.variableExist(var)) {
                VARIABLE_Instruction_Exist(currentToken);
            }
            data.pushVariable(var);
        } else {
            Variable var = FPL::Instruction::VariablesUtils::defineVariable(currentToken, data, fonction);

            var.setGlobal(true);
            if (cons) {
                var.setMutable(false);
            }

            if (data.variableExist(var)) {
                VARIABLE_Instruction_Exist(currentToken);
            }
            data.pushVariable(var);
        }
    }

    void Parser::RETIRER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto var_name = ExpectIdentifiant(currentToken);

        if (!var_name.has_value()) {
            forgotvariable(currentToken);
        }

        if (!data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        Variable var = data.getVariable(var_name->content).value();
        data.deleteVariableFromMap(var);
    }

    void Parser::IMPORTER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction) {
        auto path = ExpectValue(currentToken);

        if (!path.has_value() || path->type != Definition::Types::STRING) {
            IMPORT_pathstringormissing(currentToken);
        }

        std::ifstream fichier_fpl {path->content};
        if (!fichier_fpl) {
            IMPORT_pathstringormissing(currentToken);
        }

        std::string contentFile((std::istreambuf_iterator<char>(fichier_fpl)), (std::istreambuf_iterator<char>()));
        auto const TokenList = TokenBuilder::CodeToTokens(contentFile);
        auto next_data = FPL::Essential::Parser::Parser::executeCode(TokenList, std::nullopt, paquet, std::move(fonction));

        for (auto const& var : next_data.Variables) {
            if (var.second.isGlobal()) {
                data.pushVariable(var.second);
            }
        }
    }

    void Parser::CONVERTIR_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            forgotvariable(currentToken);
        }

        auto new_type = ExpectType(currentToken);
        if (!new_type.has_value()) {
            forgotType(currentToken);
        }

        if (!data.variableExist(var_name->content)) {
            VARIABLE_Instruction_Exist(currentToken);
        }

        Variable var = data.getVariable(var_name->content).value();

        if (var.getType() == Definition::Types::INT && new_type.value() == Definition::Types::BOOL) {
            if (var.getValue() == "1") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("vrai");
                data.pushVariable(var);
            } else if (var.getValue() == "0") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("faux");
                data.pushVariable(var);
            } else {
                CONVERT_IntToBool(currentToken);
            }
        } else if (var.getType() == Definition::Types::BOOL && new_type.value() == Definition::Types::INT) {
            if (var.getValue() == "vrai") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("1");
                data.pushVariable(var);
            } else if (var.getValue() == "faux") {
                data.deleteVariableFromMap(var);
                var.setType(Definition::Types::BOOL);
                var.setValue("0");
                data.pushVariable(var);
            } else {
                CONVERT_BoolToInt(currentToken);
            }
        } else if (var.getType() == Definition::Types::STRING && new_type.value() == Definition::Types::INT) {
            auto int_v = FPL::Utils::stringToInt(var.getValue());
            if (int_v.has_value()) {

            } else {
                CONVERT_StringToInt(currentToken);
            }
        } else if (var.getType() == Definition::Types::STRING && new_type.value() == Definition::Types::DOUBLE) {
            auto d_v = FPL::Utils::stringToDouble(var.getValue());
            if (d_v.has_value()) {

            } else {
                CONVERT_StringToDouble(currentToken);
            }
        } else {
            CONVERT_impossible(currentToken);
        }
    }

    void Parser::VERIFIER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name) {
            forgotvariable(currentToken);
        }

        if (!data.variableExist(var_name->content) && !fonction.has_value()) {
            forgotvariable(currentToken);
        } else if (data.variableExist(var_name->content)) {
            FPL::Instruction::Verifier::verifVariable(currentToken, data, var_name->content, fonction, paquet);
        } else if (fonction.has_value() && fonction->isArgument(var_name->content)) {
            FPL::Instruction::Verifier::verifArgument(currentToken, data, var_name->content, fonction, paquet);
        }
    }

    void Parser::TANT_QUE_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList, const std::optional<std::string>& paquet, std::optional<Fonctions::Fonction> fonction) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name.has_value()) {
            forgotvariable(currentToken);
        }

        auto condOperator = ExpecterConditionalOperator(currentToken);
        if (!condOperator.has_value()) {
            forgotConditionalOperator(currentToken);
        }

        auto valueToCompare = ExpectValue(currentToken);
        if (!valueToCompare.has_value()) {
            forgotValue(currentToken);
        }

        if (!ExpectOperator(currentToken, ",").has_value()) {
            TANTQUE_Vir_forgot(currentToken);
        }

        auto action = ExpectIdentifiant(currentToken);
        if (!action.has_value() || action->content != "diminuer" && action->content != "augmenter") {
            TANTQUE_wrong_action(currentToken);
        }

        auto valueToAddOrRemove = ExpectValue(currentToken);
        if (!valueToAddOrRemove.has_value()) {
            forgotValue(currentToken);
        }

        if (!ExpectOperator(currentToken, "{").has_value()) {
            forgotToOpenCode(currentToken);
        }

        std::vector<Token> innerCodeTokens;

        int nestedBrackets = 1;

        while (currentToken != tokenList.end() && nestedBrackets > 0) {
            if (currentToken->content == "{") {
                nestedBrackets++;
            } else if (currentToken->content == "}") {
                nestedBrackets--;
            }

            if (nestedBrackets > 0) {
                innerCodeTokens.push_back(*currentToken);
            }

            currentToken++;
        }

        if (valueToCompare->type == Definition::Types::STRING || valueToCompare->type == Definition::Types::BOOL) {
            TANTQUE_valueWrongType(currentToken);
        }
        if (valueToAddOrRemove->type == Definition::Types::STRING || valueToAddOrRemove->type == Definition::Types::BOOL) {
            TANTQUE_valueWrongType(currentToken);
        }

        auto var = data.getVariable(var_name->content);
        if (var.has_value()) {
            if (var->getType() == Definition::Types::STRING || var->getType() == Definition::Types::BOOL) {
                TANTQUE_varWrongType(currentToken);
            }

            if (var->getType() == Definition::Types::DOUBLE) {
                auto var_Value = FPL::Utils::stringToDouble(var->getValue());
                auto var_Compare = FPL::Utils::stringToDouble(valueToCompare->content);
                auto AddRemove = FPL::Utils::stringToDouble(valueToAddOrRemove->content);

                if (condOperator.value() == ">") {
                    while (var_Value.value() > var_Compare.value() + 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else if (condOperator.value() == ">=") {
                    while (var_Value.value() >= var_Compare.value() + 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else if (condOperator.value() == "<") {
                    while (var_Value.value() < var_Compare.value() - 1 ) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else if (condOperator.value() == "<=") {
                    while (var_Value.value() <= var_Compare.value() - 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else {
                    TANTQUE_wrong_conditionalOperator(currentToken);
                }
            } else if (var->getType() == Definition::Types::INT) {
                auto var_Value = FPL::Utils::stringToInt(var->getValue());
                auto var_Compare = FPL::Utils::stringToInt(valueToCompare->content);
                auto AddRemove = FPL::Utils::stringToInt(valueToAddOrRemove->content);

                if (condOperator.value() == ">") {
                    while (var_Value.value() > var_Compare.value() + 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else if (condOperator.value() == ">=") {
                    while (var_Value.value() >= var_Compare.value() + 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else if (condOperator.value() == "<") {
                    while (var_Value.value() < var_Compare.value() - 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else if (condOperator.value() == "<=") {
                    while (var_Value.value() <= var_Compare.value() - 1) {
                        if (action->content == "augmenter") {
                            var_Value.value() += AddRemove.value();
                        } else {
                            var_Value.value() -= AddRemove.value();
                        }
                        data.updateVariableValue(var.value(), std::to_string(var_Value.value()));
                        auto new_data = executeCode(innerCodeTokens, data, paquet, fonction);
                        for (auto &e : new_data.Variables) {
                            if (data.variableExist(e.second)) {
                                data.updateVariableValue(data.getVariable(e.second.getName()).value(), e.second.getValue());
                            }
                        }
                    }
                } else {
                    TANTQUE_wrong_conditionalOperator(currentToken);
                }
            }
        }
        else {
            forgotvariable(currentToken);
        }
    }

    void Parser::PAQUET_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, std::vector<Token> tokenList, std::optional<std::string> paquet, std::optional<Fonctions::Fonction> fonction) {
        auto paq_name = ExpectIdentifiant(currentToken);
        if (!paq_name.has_value()) {
            forgotName(currentToken);
        }

        std::string paquetName = paq_name->content;

        if (paquet.has_value()) {
            paquetName = paquet.value() + "." + paq_name->content;
        }

        if (!ExpectOperator(currentToken, "{").has_value()) {
            forgotToOpenCode(currentToken);
        }

        std::vector<Token> innerCodeTokens;

        int nestedBrackets = 1;

        while (currentToken != tokenList.end() && nestedBrackets > 0) {
            if (currentToken->content == "{") {
                nestedBrackets++;
            } else if (currentToken->content == "}") {
                nestedBrackets--;
            }

            if (nestedBrackets > 0) {
                innerCodeTokens.push_back(*currentToken);
            }

            currentToken++;
        }

        auto new_data = executeCode(innerCodeTokens, data, paquetName, std::move(fonction));

        for (auto const& variables : new_data.Variables) {
            if (!data.variableExist(variables.second.getName())) {
                data.pushVariable(variables.second);
            }
        }
    }

    void Parser::DEFINIR_Instruction(std::vector<Token>::iterator& currentToken, Data::Data& data, std::vector<Token> tokenList, std::optional<std::string> paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto f_name = ExpectIdentifiant(currentToken);
        if (!f_name.has_value()) {
            forgotName(currentToken);
        }

        std::string funcName = f_name->content;
        if (paquet.has_value()) {
            funcName = paquet.value() + "." + f_name->content;
        }

        // Get Arguments:
        if (ExpectOperator(currentToken, "(").has_value()) {
            FPL::Definition::Fonctions::Fonction f;
            f.setName(funcName);

            while (!ExpectOperator(currentToken, ")").has_value()) {
                auto arg_type = ExpectType(currentToken);
                if (!arg_type.has_value()) {
                    forgotType(currentToken);
                }

                auto arg_name = ExpectIdentifiant(currentToken);
                if (!arg_name.has_value()) {
                    forgotName(currentToken);
                }

                FPL::Definition::Fonctions::Argument arg;
                arg.setName(arg_name->content);
                arg.setType(arg_type.value());

                f.addArgument(arg);

                if (ExpectOperator(currentToken, ")").has_value()) {
                    break;
                } else if (!ExpectOperator(currentToken, ",").has_value()) {
                    FUNC_needToAddParameter(currentToken);
                }
            }

            if (!ExpectOperator(currentToken, "{").has_value()) {
                forgotToOpenCode(currentToken);
            }

            std::vector<Token> innerCodeTokens;

            int nestedBrackets = 1;

            while (currentToken != tokenList.end() && nestedBrackets > 0) {
                if (currentToken->content == "{") {
                    nestedBrackets++;
                } else if (currentToken->content == "}") {
                    nestedBrackets--;
                }

                if (nestedBrackets > 0) {
                    innerCodeTokens.push_back(*currentToken);
                }

                currentToken++;
            }

            f.setTokens(innerCodeTokens);

            data.pushFonction(f);
        } else {
            forgotOpenParenthese(currentToken);
        }
    }

    void Parser::APPELER_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, std::vector<Token>& tokenList, const std::optional<std::string>& paquet, const std::optional<Fonctions::Fonction>& fonction) {
        auto f_name = ExpectIdentifiant(currentToken);
        if (!f_name) {
            forgotName(currentToken);
        }

        if (!data.isFonction(f_name->content)) {
            FUNC_doesNotExist(currentToken);
        }

        auto f = data.getFonction(f_name->content).value();

        if (f.getArgumentsSize() == 0) {
            auto next_data = executeCode(f.getTokensFunction(), data, paquet, f);

            for (auto const& v : next_data.Variables) {
                if (v.second.isGlobal()) {
                    data.pushVariable(v.second);
                }
            }
        } else {
            if(!ExpectOperator(currentToken, "(").has_value()) {
                forgotOpenParenthese(currentToken);
            }

            int totalWaitingArgs = f.getArgumentsSize();
            while (totalWaitingArgs > 0) {
                auto possibleArgName = ExpectIdentifiant(currentToken);
                if (!possibleArgName || !data.isFonctionArgument(f.getName(), possibleArgName->content)) {
                    FUNC_needArg(currentToken);
                }

                auto possibleValue = ExpectValue(currentToken);
                if(!possibleValue.has_value()) {
                    forgotValue(currentToken);
                }

                auto currentArg = data.getFonctionArgument(f.getName(), possibleArgName->content);

                if (currentArg->getType() != possibleValue->type) {
                    FUNC_wrongTypeArg(currentToken);
                }

                Variable nextVar;
                nextVar.setName(possibleArgName->content);
                nextVar.setGlobal(false);
                nextVar.setIsArgument(true);
                nextVar.setType(f.getArgument(possibleArgName->content)->getType());
                nextVar.setValue(possibleValue.value().content);
                data.pushVariable(nextVar);

                totalWaitingArgs--;
                if (ExpectOperator(currentToken, ")").has_value() && totalWaitingArgs > 0) {
                    FUNC_needArg(currentToken);
                } else if (ExpectOperator(currentToken, ")").has_value() && totalWaitingArgs == 0) {
                    break;
                } else if (!ExpectOperator(currentToken, ")").has_value() && totalWaitingArgs > 0 && !ExpectOperator(currentToken, ",").has_value()) {
                    FUNC_needToAddArgumentInCall(currentToken);
                }
            }

            auto next_data = executeCode(f.getTokensFunction(), data, paquet, f);

            for (auto const& v : next_data.Variables) {
                if (v.second.isArgument()) {
                    next_data.deleteVariableFromMap(v.second);
                    data.deleteVariableFromMap(v.second);
                } else if (v.second.isGlobal()) {
                    data.pushVariable(v.second);
                }
            }
        }
    }

    void Parser::MATH_Instruction(std::vector<Token>::iterator &currentToken, Data::Data &data, std::vector<Token> &tokenList, const std::optional<std::string> &paquet, const std::optional<Fonctions::Fonction> &fonction) {
        auto var_name = ExpectIdentifiant(currentToken);
        if (!var_name) {
            forgotName(currentToken);
        }

        if (!ExpectOperator(currentToken, "[").has_value()) {
            forgotOpenBloc(currentToken);
        }

        std::vector<std::string> innerCodeTokens;

        while (currentToken != tokenList.end() && !ExpectOperator(currentToken, "]").has_value()) {
            innerCodeTokens.push_back(currentToken->content);
            currentToken++;
        }
        std::string MathInsContent = FPL::Utils::StringVectorToString(innerCodeTokens);
        std::vector<MathParser::Token> contentMathTokens = MathParser::TokenBuilding::ParserTokens(MathInsContent);
        double result = MATHPARSER_Parser(contentMathTokens);

        Variable var(var_name->content, std::to_string(result), Definition::Types::DOUBLE);
        data.pushVariable(var);
    }
}