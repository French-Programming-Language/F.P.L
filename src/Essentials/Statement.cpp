#include "Statement.h"

namespace FPL::Statement {
    Statement::Statement(StatementKind kind, std::string name, FPL::Types::Types type) {
        StatementType = type;
        StatementName = name;
        StatementKind{kind};
    }
}