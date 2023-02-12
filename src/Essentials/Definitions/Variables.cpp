#include "Variables.h"

namespace FPL {
    std::ostream& operator<<(std::ostream &flux, FPL::VariableDef const& var) {
        flux << "Une variable du nom de " << var.VariableName << ", a pour valeur " << var.VariableValue << ", pour type " << var.VariableType.Name << ", globale : " << var.IsGlobal;
        return flux;
    }

    bool operator==(const VariableDef &v1, const VariableDef &v2) {
        return v1.VariableType.Type == v2.VariableType.Type;
    }

    bool operator!=(const VariableDef &v1, const VariableDef &v2) {
        return v1.VariableType.Type != v2.VariableType.Type;
    }
}