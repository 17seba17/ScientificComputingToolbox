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

# Publicly expose internal include directory
target_include_directories(DataAnalysisLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/StatisticalAnalyser/include>
    # Espone la path di Boost pubblicamente (se DataAnalyser.hpp usa Boost)
    PUBLIC ${BOOST_INCLUDE_DIR}
)

# Link dependencies
target_link_libraries(DataAnalysisLib
    PUBLIC
        Eigen3::Eigen 
        muparserx
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


# 2. External System Headers (MUPARSERX FIX)
# Usiamo SYSTEM PUBLIC per garantire che questa path assoluta 
# venga propagata all'eseguibile che include FunctionsArray.hpp
add_library(ODESolverLib SHARED ${ODE_SOLVER_SRCS} ${ODE_SOLVER_HDRS})

# 1. Internal Interface Headers (needed by consumers)
target_include_directories(ODESolverLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ODE/include>
)

# 2. FIX: Aggiungi il percorso genitore che contiene la directory 'parser/'
# Stiamo usando SYSTEM PUBLIC perché è un header esterno e non deve generare warning
target_include_directories(ODESolverLib SYSTEM PUBLIC
    /usr/local/include
)

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