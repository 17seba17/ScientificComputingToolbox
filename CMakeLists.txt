cmake_minimum_required(VERSION 3.12)
project(ScientificFramework VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Required for shared libraries


add_subdirectory(eigen)
add_subdirectory(muparserx)

add_library(Muparserx_Includes INTERFACE)
target_include_directories(Muparserx_Includes SYSTEM INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/muparserx/include>
    # Oppure il percorso che contiene la cartella 'parser/'
)
set(BOOST_INCLUDE_DIR "/usr/local/boost_1_89_0")



add_subdirectory(src)
add_subdirectory(apps)
