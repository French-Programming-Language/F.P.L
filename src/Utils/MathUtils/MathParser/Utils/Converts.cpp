#include "Converts.h"

double convertDouble(std::string& n) {
    try {
        double v = std::stod(n);
        return v;
    }
    catch (std::invalid_argument const& ex) {
        std::cout << "It can not be a double/int value !" << " Final error: " << ex.what() << std::endl;
    }

    return 0;
}