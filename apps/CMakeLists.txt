# =========================================================
# cmake apps
# =========================================================

# --- Esempio 1: Eseguibile per l'ODE Solver ---

set(ODE_APP_NAME ode_solver_app)
add_executable(${ODE_APP_NAME} resolve_ode.cpp)

# Linkando ODESolverLib, l'app eredita automaticamente:
# - Il path di include di ODE/include
# - Il path di include di muparserx root (per parser/mpParser.h)
# - I flag di compilazione di Eigen
target_link_libraries(${ODE_APP_NAME}
    PRIVATE
        ODESolverLib
)

# --- Esempio 2: Eseguibile per Data Analysis ---

set(DATA_APP_NAME data_analysis_app)
add_executable(${DATA_APP_NAME} analyse_file.cpp)

target_link_libraries(${DATA_APP_NAME}
    PRIVATE
        DataAnalysisLib
)

# --- Installazione degli Eseguibili ---

install(TARGETS ${ODE_APP_NAME} ${DATA_APP_NAME}
    RUNTIME DESTINATION bin
)