#include "TantQue_Loop.h"

namespace FPL::Instruction::TantQue {
    void increment_int_operatorLowerUpper(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd) {
        int variable_v = stringToInt(var.VariableValue, "");

        if (variable_v < value) {
            int start = 0;
            while (variable_v < value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v += numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }

    void increment_double_operatorLowerUpper(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd) {
        double variable_v = stringToDouble(var.VariableValue, "");

        if (variable_v < value) {
            int start = 0;
            while (variable_v < value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v+=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }

    void decrement_int_operatorLowerUpper(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd) {
        int variable_v = stringToInt(var.VariableValue, "");

        if (variable_v < value) {
            int start = 0;
            while (variable_v < value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v-=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }

    void decrement_double_operatorLowerUpper(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd) {
        double variable_v = stringToDouble(var.VariableValue, "");

        if (variable_v < value) {
            int start = 0;
            while (variable_v < value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v-=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }





    void increment_int_operatorUpperLower(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd) {
        int variable_v = stringToInt(var.VariableValue, "");

        if (variable_v > value) {
            int start = 0;
            while (variable_v > value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v+=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }

    void increment_double_operatorUpperLower(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd) {
        double variable_v = stringToDouble(var.VariableValue, "");

        if (variable_v > value) {
            int start = 0;
            while (variable_v > value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v+=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }


    void decrement_int_operatorUpperLower(VariableDef& var, int value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, int numberToAdd) {
        int variable_v = stringToInt(var.VariableValue, "");

        if (variable_v > value) {
            int start = 0;
            while (variable_v > value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v-=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }

    void decrement_double_operatorUpperLower(VariableDef& var, double value, Data::Data& data, std::vector<Tokenizer::Token>& TantQue_Tokens, std::optional<FPL::FonctionDef>& fonction, double numberToAdd) {
        double variable_v = stringToDouble(var.VariableValue, "");

        if (variable_v > value) {
            int start = 0;
            while (variable_v > value) {
                if (start == 0) {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                    start++;
                } else {
                    Parser::Parser::executeContentCode(TantQue_Tokens, fonction, std::nullopt, data);
                }

                variable_v-=numberToAdd;
                data.updateValue(var.VariableName, std::to_string(variable_v));
            }
        } // Si non est bien, on arrête l'instruction 'tant que'
    }
}