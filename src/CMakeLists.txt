#Module A
set(DATA_ANALYSIS_HDRS
    StatisticalAnalyser/include/DataAnalyser.hpp
    StatisticalAnalyser/include/ProcessedData.hpp
    StatisticalAnalyser/include/RawData.hpp
    StatisticalAnalyser/include/RawDataJSON.hpp
    StatisticalAnalyser/include/RawDataCSV.hpp
    StatisticalAnalyser/include/Iterator.hpp
    StatisticalAnalyser/include/detail/InfoColumn.hpp
    StatisticalAnalyser/include/detail/Type.hpp
)

set(DATA_ANALYSIS_SRCS
    StatisticalAnalyser/src/DataAnalyser.cpp
    StatisticalAnalyser/src/ProcessedData.cpp
    StatisticalAnalyser/src/RawData.cpp
    StatisticalAnalyser/src/RawDataCSV.cpp
    StatisticalAnalyser/src/RawDataJSON.cpp
)

add_library(DataAnalysisLib SHARED ${DATA_ANALYSIS_SRCS} ${DATA_ANALYSIS_HDRS})

target_include_directories(DataAnalysisLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/StatisticalAnalyser/include>
    $<INSTALL_INTERFACE:include/ScientificComputingToolbox>
)

target_link_libraries(DataAnalysisLib
    PUBLIC
        Eigen3::Eigen 
        muparserx
        Boost::headers
)

#Module D
set(ODE_SOLVER_HDRS
    ODE/include/ButcherTableau.hpp
    ODE/include/FunctionsArray.hpp
    ODE/include/ODE.hpp
)

set(ODE_SOLVER_SRCS
    ODE/src/ButcherTableau.cpp
)

add_library(ODESolverLib SHARED ${ODE_SOLVER_SRCS} ${ODE_SOLVER_HDRS})


target_include_directories(ODESolverLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ODE/include>
    $<INSTALL_INTERFACE:include/ScientificComputingToolbox>
)

target_include_directories(ODESolverLib SYSTEM PUBLIC
    $<BUILD_INTERFACE:${MUPARSERX_ROOT_DIR}>
)

target_link_libraries(ODESolverLib
    PUBLIC
        Eigen3::Eigen
        muparserx
)


install(TARGETS DataAnalysisLib ODESolverLib
    EXPORT ScientificComputingToolboxTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/ScientificComputingToolbox
)