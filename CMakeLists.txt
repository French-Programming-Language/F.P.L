cmake_minimum_required(VERSION 3.22)
project(French_Programming_Language)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(French_Programming_Language
        main.cpp

        src/Essentials/Tokenizer.cpp
        src/Essentials/Tokenizer.h
        src/Essentials/Parser.cpp
        src/Essentials/Parser.h
        src/Essentials/Types.cpp
        src/Essentials/Types.h
        src/Essentials/Statement.cpp
        src/Essentials/Statement.h
        src/Essentials/Utils/Expecter.cpp
        src/Essentials/Utils/Expecter.h
        src/Essentials/Utils/Data.cpp
        src/Essentials/Utils/Data.h
        src/Essentials/Utils/ErrorsCodeManagement.cpp
        src/Essentials/Utils/ErrorsCodeManagement.h
        src/Essentials/Definitions/Variables.cpp
        src/Essentials/Definitions/Variables.h
        src/Essentials/MathUtils/Converts.h
        src/Essentials/MathUtils/Converts.cpp
        src/Essentials/Utils/Vectors.cpp
        src/Essentials/Utils/Vectors.h

        src/Instructions/Prints.cpp
        src/Instructions/Prints.h
        src/Instructions/Inputs.cpp
        src/Instructions/Inputs.h

        src/Essentials/MathUtils/MathParser/MathTokenizer.cpp
        src/Essentials/MathUtils/MathParser/MathTokenizer.h
        src/Essentials/MathUtils/MathParser/MathParser.cpp
        src/Essentials/MathUtils/MathParser/MathParser.h
        src/Essentials/MathUtils/MathParser/Utils/Converts.cpp
        src/Essentials/MathUtils/MathParser/Utils/Converts.h
        src/Essentials/Definitions/Fonction.cpp src/Essentials/Definitions/Fonction.h)
