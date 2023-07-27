#include "VectorsTo.h"

namespace FPL::Utils {
    std::string StringVectorToString(std::vector<std::string>& vec) {
        std::ostringstream oss;
        if (!vec.empty()) {
            std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<std::string>(oss, " "));
            oss << vec.back();
        }

        return oss.str();
    }
}