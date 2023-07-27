#pragma once

#include <iostream>
#include <optional>

namespace FPL::Utils {
    std::optional<int> stringToInt(const std::string& v);
    std::optional<double> stringToDouble(const std::string& v);
}