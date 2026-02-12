cmake_minimum_required(VERSION 3.21)
project(Chip_8_Emu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "G:/c++/librerie/SFML-3.0.2/lib/cmake/SFML")

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(Chip_8_Emu main.cpp)

target_link_libraries(Chip_8_Emu
        SFML::Graphics
        SFML::Window
        SFML::System
)