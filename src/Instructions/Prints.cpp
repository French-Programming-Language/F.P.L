#include "Prints.h"

namespace FPL::Instruction::Prints {
    void managementPrint_VARIABLE(FPL::Data::Data &data, FPL::VariableDef &var) {
        auto conditionOperator = ExpectConditionOperator(data);
        if (conditionOperator.has_value()) {
            auto conditionValue = ExpectValue(data);
            if (!conditionValue.has_value()) {needValueNextOperatorCondition(data);}

            if (conditionOperator == "=") {
                if (var.VariableType.Type == Types::INT) {
                    int varV = stringToInt(var.VariableValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT("=", varV, condV);
                } else if (var.VariableType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(var.VariableValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE("=", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == ">") {
                if (var.VariableType.Type == Types::INT) {
                    int varV = stringToInt(var.VariableValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT(">", varV, condV);
                } else if (var.VariableType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(var.VariableValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE(">", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == "<") {
                if (var.VariableType.Type == Types::INT) {
                    int varV = stringToInt(var.VariableValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT("<", varV, condV);
                } else if (var.VariableType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(var.VariableValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE("<", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == ">=") {
                if (var.VariableType.Type == Types::INT) {
                    int varV = stringToInt(var.VariableValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT(">=", varV, condV);
                } else if (var.VariableType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(var.VariableValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE(">=", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == "<=") {
                if (var.VariableType.Type == Types::INT) {
                    int varV = stringToInt(var.VariableValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT("<=", varV, condV);
                } else if (var.VariableType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(var.VariableValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE("<=", varV, condV);
                } else {
                    wrongType(data);
                }
            }
        } else {
            std::cout << var.VariableValue;
        }
    }

    void managementPrint_ARGUMENT(FPL::Data::Data &data, std::optional<FPL::FonctionArgumentDef> &arg) {
        auto conditionOperator = ExpectConditionOperator(data);
        if (conditionOperator.has_value()) {
            auto conditionValue = ExpectValue(data);
            if (!conditionValue.has_value()) {needValueNextOperatorCondition(data);}

            if (conditionOperator == "=") {
                if (arg->ArgumentType.Type == Types::INT) {
                    int varV = stringToInt(arg->ArgumentValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT("=", varV, condV);
                } else if (arg->ArgumentType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(arg->ArgumentValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE("=", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == ">") {
                if (arg->ArgumentType.Type == Types::INT) {
                    int varV = stringToInt(arg->ArgumentValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT(">", varV, condV);
                } else if (arg->ArgumentType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(arg->ArgumentValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE(">", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == "<") {
                if (arg->ArgumentType.Type == Types::INT) {
                    int varV = stringToInt(arg->ArgumentValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT("<", varV, condV);
                } else if (arg->ArgumentType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(arg->ArgumentValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE("<", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == ">=") {
                if (arg->ArgumentType.Type == Types::INT) {
                    int varV = stringToInt(arg->ArgumentValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT(">=", varV, condV);
                } else if (arg->ArgumentType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(arg->ArgumentValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE(">=", varV, condV);
                } else {
                    wrongType(data);
                }
            } else if (conditionOperator == "<=") {
                if (arg->ArgumentType.Type == Types::INT) {
                    int varV = stringToInt(arg->ArgumentValue, "");
                    int condV = stringToInt(conditionValue->StatementName, "");
                    printWithOperatorCondition_INT("<=", varV, condV);
                } else if (arg->ArgumentType.Type == Types::DOUBLE) {
                    double varV = stringToDouble(arg->ArgumentValue, "");
                    double condV = stringToDouble(conditionValue->StatementName, "");
                    printWithOperatorCondition_DOUBLE("<=", varV, condV);
                } else {
                    wrongType(data);
                }
            }
        } else {
            std::cout << arg->ArgumentValue;
        }
    }

    void printWithOperatorCondition_INT(std::string_view currOP, int a, int b) {
        if (currOP == "=") {
            if (a == b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == "<") {
            if (a < b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == ">") {
            if (a > b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == ">=") {
            if (a >= b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == "<=") {
            if (a <= b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        }
    }

    void printWithOperatorCondition_DOUBLE(std::string_view currOP, double a, double b) {
        if (currOP == "=") {
            if (a == b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == "<") {
            if (a < b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == ">") {
            if (a > b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == ">=") {
            if (a >= b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        } else if (currOP == "<=") {
            if (a <= b) {
                std::cout << "vrai";
            } else {
                std::cout << "faux";
            }
        }
    }
}