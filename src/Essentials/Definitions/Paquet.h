#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace FPL::Paquet{
    class Paquet {
    public:
        std::string PaquetName;
        std::vector<std::string> PaquetContent;
    };
}