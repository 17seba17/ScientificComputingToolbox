cmake_minimum_required(VERSION 3.16)
project(ScientificToolbox CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)


find_package(Eigen3 REQUIRED)
find_package(muparserx REQUIRED)
find_package(Boost 1.89.0 REQUIRED) 

#add_subdirectory(src)
#add_subdirectory(app)
#add_subdirectory(tests)

set(STB_INSTALL_DIR ScientificToolbox)