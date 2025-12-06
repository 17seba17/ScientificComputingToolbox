# =========================================================
# cmake src
# =========================================================

# --- MODULE A: Data Analysis Library ---

set(DATA_ANALYSIS_HDRS
    StatisticalAnalyser/include/DataAnalyser.hpp
    StatisticalAnalyser/include/ProcessData.hpp
    StatisticalAnalyser/include/RawData.hpp
    StatisticalAnalyser/include/RawDataJSON.hpp
    StatisticalAnalyser/include/RawDataCSV.hpp
    StatisticalAnalyser/include/Iterator.hpp
    StatisticalAnalyser/include/detail/InfoColumn.hpp
    StatisticalAnalyser/include/detail/Type.hpp
)

set(DATA_ANALYSIS_SRCS
    StatisticalAnalyser/src/RawDataJSON.cpp
)

add_library(DataAnalysisLib SHARED ${DATA_ANALYSIS_SRCS} ${DATA_ANALYSIS_HDRS})

target_include_directories(DataAnalysisLib PUBLIC
    # Include interni per chi usa la libreria
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/StatisticalAnalyser/include>
    $<INSTALL_INTERFACE:include/ScientificFramework>
)

target_link_libraries(DataAnalysisLib
    PUBLIC
        Eigen3::Eigen 
        muparserx
        Boost::headers # Linka gli header di Boost trovati nella root
)

# --- MODULE B: ODE Solver Library ---

set(ODE_SOLVER_HDRS
    ODE/include/ButcherTableau.hpp
    ODE/include/FunctionsArray.hpp
    ODE/include/ODE.hpp
)

set(ODE_SOLVER_SRCS
    ODE/src/ButcherTableau.cpp
)

add_library(ODESolverLib SHARED ${ODE_SOLVER_SRCS} ${ODE_SOLVER_HDRS})

# GESTIONE INCLUDE PERFETTA:
# 1. La cartella include locale di ODE
# 2. La root di muparserx (per permettere #include <parser/mpParser.h>)
# Usiamo SYSTEM per evitare warning da muparserx
target_include_directories(ODESolverLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ODE/include>
    $<INSTALL_INTERFACE:include/ScientificFramework>
)

target_include_directories(ODESolverLib SYSTEM PUBLIC
    $<BUILD_INTERFACE:${MUPARSERX_ROOT_DIR}>
)

# Link dependencies
# Usiamo PUBLIC perché gli header di ODESolverLib includono header di Eigen e Muparserx
target_link_libraries(ODESolverLib
    PUBLIC
        Eigen3::Eigen
        muparserx
)

# --- Install Targets ---

install(TARGETS DataAnalysisLib ODESolverLib
    EXPORT ScientificFrameworkTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/ScientificFramework
)