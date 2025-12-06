cmake_minimum_required(VERSION 3.12)
project(ScientificFramework VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Necessario per librerie condivise

add_subdirectory(eigen)

add_subdirectory(muparserx)


set(MUPARSERX_ROOT_DIR "${CMAKE_SOURCE_DIR}/muparserx")


find_package(Boost REQUIRED) 

add_subdirectory(src)
add_subdirectory(apps)