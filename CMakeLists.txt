cmake_minimum_required(VERSION 3.25)
project(FPL)

set(CMAKE_CXX_STANDARD 23)

add_executable(FPL
        main.cpp
        src/Essentials/Tokenizer/Tokenizer.cpp
        src/Essentials/Tokenizer/Tokenizer.h
        src/Essentials/Parser/Parser.cpp
        src/Essentials/Parser/Parser.h
        src/Essentials/Data/Data.cpp
        src/Essentials/Data/Data.h
        src/Essentials/Definitions/Variables/Variables.cpp
        src/Essentials/Definitions/Variables/Variables.h
        src/Essentials/Definitions/Types/Types.cpp
        src/Essentials/Definitions/Types/Types.h
        src/Essentials/Expecter/Expecter.cpp
        src/Essentials/Expecter/Expecter.h
        src/Essentials/ErrorsManager/ErrorsManager.cpp
        src/Essentials/ErrorsManager/ErrorsManager.h
        src/Essentials/Definitions/Value/Value.cpp
        src/Essentials/Definitions/Value/Value.h
        src/Instructions/envoyer/Envoyer.h
        src/Instructions/envoyer/Envoyer.cpp
        src/Utils/stringTo.h src/Utils/stringTo.cpp
        src/Instructions/saisir/Saisir.h
        src/Instructions/saisir/Saisir.cpp
        src/Instructions/VariablesUtils/Variables.cpp
        src/Instructions/VariablesUtils/Variables.h
        src/Utils/VectorsTo.cpp
        src/Utils/VectorsTo.h
        src/Essentials/Definitions/Fonctions/Fonctions.cpp
        src/Essentials/Definitions/Fonctions/Fonctions.h
        src/Instructions/Conditions/verifier.cpp
        src/Instructions/Conditions/verifier.h
        src/Utils/MathUtils/Converts.h
        src/Utils/MathUtils/Converts.cpp
        src/Utils/MathUtils/MathParser/Utils/Converts.h
        src/Utils/MathUtils/MathParser/Utils/Converts.cpp
        src/Utils/MathUtils/MathParser/MathParser.h
        src/Utils/MathUtils/MathParser/MathParser.cpp
        src/Utils/MathUtils/MathParser/MathTokenizer.h
        src/Utils/MathUtils/MathParser/MathTokenizer.cpp
        )
