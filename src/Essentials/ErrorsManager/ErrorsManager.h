#include <iostream>
#include "../Data/Data.h"

using namespace FPL::Essential::Tokenizer;

void forgotValue(std::vector<Token>::iterator token);
void forgotName(std::vector<Token>::iterator token);
void forgotType(std::vector<Token>::iterator token);
void forgotEqualOperator(std::vector<Token>::iterator token);
void differentTypes(std::vector<Token>::iterator token);
void VARIABLE_Instruction_Exist(std::vector<Token>::iterator token);
void CHANGER_Instruction_unknowVariable(std::vector<Token>::iterator token);
void missingparameter(std::vector<Token>::iterator token);
void invalidparameter(std::vector<Token>::iterator token);
void unknowfile(std::vector<Token>::iterator token);
void variable_no_mutable(std::vector<Token>::iterator token);
void forgotvariable(std::vector<Token>::iterator token);
void IMPORT_pathstringormissing(std::vector<Token>::iterator token);
void CONVERT_IntToBool(std::vector<Token>::iterator token);
void CONVERT_BoolToInt(std::vector<Token>::iterator token);
void CONVERT_StringToInt(std::vector<Token>::iterator token);
void CONVERT_StringToDouble(std::vector<Token>::iterator token);
void CONVERT_impossible(std::vector<Token>::iterator token);
void forgotToOpenCode(std::vector<Token>::iterator token);
void VERIFIER_CAS_title(std::vector<Token>::iterator token);
void VERIFIER_CAS_openCode(std::vector<Token>::iterator token);
void forgotConditionalOperator(std::vector<Token>::iterator token);
void TANTQUE_Vir_forgot(std::vector<Token>::iterator token);
void TANTQUE_wrong_action(std::vector<Token>::iterator token);
void TANTQUE_wrong_conditionalOperator(std::vector<Token>::iterator token);
void forgotOpenParenthese(std::vector<Token>::iterator token);
void FUNC_needToAddParameter(std::vector<Token>::iterator token);
void FUNC_doesNotExist(std::vector<Token>::iterator token);
void FUNC_needArg(std::vector<Token>::iterator token);
void FUNC_wrongTypeArg(std::vector<Token>::iterator token);
void FUNC_needToAddArgumentInCall(std::vector<Token>::iterator token);
void TANTQUE_varWrongType(std::vector<Token>::iterator token);
void TANTQUE_valueWrongType(std::vector<Token>::iterator token);
void forgotOpenBloc(std::vector<Token>::iterator token);