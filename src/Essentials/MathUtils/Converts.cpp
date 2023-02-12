#include "Converts.h"

int stringToInt(std::string value, std::string_view message) {
    try {
        int v = std::stoi(value);
        return v;
    }
    catch (std::invalid_argument const& ex) {
        std::cout << message << "Erreur final : " << ex.what() << std::endl;
    }
    return 0;
}

double stringToDouble(std::string value, std::string_view message) {
    try {
        double v = std::stod(value);
        return v;
    }
    catch (std::invalid_argument const& ex) {
        std::cout << message << "Erreur final : " << ex.what() << std::endl;
    }
    return 0;
}