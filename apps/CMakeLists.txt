

set(ODE_APP_NAME ode_solver_app)
add_executable(${ODE_APP_NAME} resolve_ode.cpp)

target_link_libraries(${ODE_APP_NAME}
    PRIVATE
        ODESolverLib
)


set(DATA_APP_NAME data_analysis_app)
add_executable(${DATA_APP_NAME} analyse_file.cpp)

target_link_libraries(${DATA_APP_NAME}
    PRIVATE
        DataAnalysisLib
)


install(TARGETS ${ODE_APP_NAME} ${DATA_APP_NAME}
    RUNTIME DESTINATION bin
)