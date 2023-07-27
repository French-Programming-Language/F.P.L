#include "stringTo.h"

namespace FPL::Utils {
    std::optional<int> stringToInt(const std::string& v) {
        try {
            int r = std::stoi(v);
            return r;
        }
        catch (std::invalid_argument const& ex) {
            return std::nullopt;
        }
    }

    std::optional<double> stringToDouble(const std::string& v) {
        try {
            double r = std::stod(v);
            return r;
        }
        catch (std::invalid_argument const& ex) {
            return std::nullopt;
        }
    }
}