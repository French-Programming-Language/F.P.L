#include <algorithm>
#include "Expecter.h"

std::optional<Token> ExpectIdentifiant(std::vector<Token>::iterator &current) {
    if (current->type == IDENTIFIANT) {
        auto returnt = current;
        returnt->content.erase(std::remove_if(returnt->content.begin(), returnt->content.end(), isspace), returnt->content.end());
        current++;
        return *returnt;
    }
    return std::nullopt;
}

std::optional<Token> ExpectOperator(std::vector<Token>::iterator &current, std::string_view o) {
    if (current->type == OPERATOR && o.empty()) {
        auto returnt = current;
        current++;
        return *returnt;
    } else if (current->type == OPERATOR && !o.empty() && current->content == o) {
        auto returnt = current;
        current++;
        return *returnt;
    }
    return std::nullopt;
}

std::optional<std::string> ExpecterConditionalOperator(std::vector<Token>::iterator &current) {
    if (ExpectOperator(current, ">").has_value()) {
        if (ExpectOperator(current, "=").has_value()) {
            return ">=";
        } else {
            return ">";
        }
    } else if (ExpectOperator(current, "<").has_value()) {
        if (ExpectOperator(current, "=").has_value()) {
            return "<=";
        } else {
            return "<";
        }
    }
    return std::nullopt;
}

std::optional<FPL::Definition::Values::Value> ExpectValue(std::vector<Token>::iterator &current) {
    auto returnt = current;
    if (current->type == INT || current->type == DOUBLE || current->type == STRING) {
        if (current->type == INT) {
            FPL::Definition::Values::Value v(FPL::Definition::Types::INT, returnt->content);
            current++;
            return v;
        } else if (current->type == DOUBLE) {
            FPL::Definition::Values::Value v(FPL::Definition::Types::DOUBLE, returnt->content);
            current++;
            return v;
        } else if (current->type == STRING) {
            returnt->content.erase(std::remove(returnt->content.begin(), returnt->content.end(), '\"'), returnt->content.end());
            FPL::Definition::Values::Value v(FPL::Definition::Types::STRING, returnt->content);
            current++;
            return v;
        }
    } else if (current->type == IDENTIFIANT && current->content == "vrai" || current->type == IDENTIFIANT && current->content == "faux") {
        current++;
        FPL::Definition::Values::Value v(FPL::Definition::Types::BOOL, returnt->content);
        return v;
    }
    return std::nullopt;
}

std::optional<FPL::Definition::Types::Type> ExpectType(std::vector<Token>::iterator &current) {
    if (current->type == IDENTIFIANT) {
        auto returnt = current;
        returnt->content.erase(remove_if(returnt->content.begin(), returnt->content.end(), isspace), returnt->content.end());
        if (current->content == "entier") {
            //return *returnt;
            current++;
            return FPL::Definition::Types::INT;
        } else if (current->content == "decimal") {
            current++;
            return FPL::Definition::Types::DOUBLE;
        } else if (current->content == "bool" || current->content == "booleen" ) {
            current++;
            return FPL::Definition::Types::BOOL;
        } else if (current->content == "texte") {
            current++;
            return FPL::Definition::Types::STRING;
        }
    }
    return std::nullopt;
}

bool ExpectEqualOperator(std::vector<Token>::iterator &current) {
    if (ExpectOperator(current, "-").has_value()) {
        if (ExpectOperator(current, ">").has_value()) {
            return true;
        }
    }
    return false;
}