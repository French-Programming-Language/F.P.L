#include "Inputs.h"

namespace FPL::Instruction::Inputs {
    std::string returnInputFinalValue(FPL::Types::BUILTIN_TYPE& type, FPL::Data::Data& data) {
        std::string finalValue;
        if (type == FPL::Types::INT) {
            int v;
            std::cin >> v;
            finalValue = std::to_string(v);
            if (finalValue == "0" || v == 0) {
                inputTypeError(data);
            }
            std::cout << std::endl;
        } else if (type == FPL::Types::DOUBLE) {
            double v;
            std::cin >> v;
            finalValue = std::to_string(v);
            if (finalValue == "0" || v == 0) {
                inputTypeError(data);
            }
            std::cout << std::endl;
        } else {
            std::cin >> finalValue;
        }

        return finalValue;
    }
}