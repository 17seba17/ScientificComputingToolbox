# =========================================================
# cmake apps
# =========================================================

# --- Esempio 1: Eseguibile per l'ODE Solver ---

set(ODE_APP_NAME ode_solver_app)
set(ODE_APP_SRC resolve_ode.cpp)

add_executable(${ODE_APP_NAME} ${ODE_APP_SRC})

# Colleghiamo ODESolverLib. Tutte le sue proprietà PUBLIC (inclusi gli header 
# MuparserX ora corretti) vengono ereditate automaticamente.
target_link_libraries(${ODE_APP_NAME}
    PRIVATE
        ODESolverLib
)

# --- Esempio 2: Eseguibile per Data Analysis ---

set(DATA_APP_NAME data_analysis_app)
set(DATA_APP_SRC analyse_file.cpp)

add_executable(${DATA_APP_NAME} ${DATA_APP_SRC})

target_link_libraries(${DATA_APP_NAME}
    PRIVATE
        DataAnalysisLib
)


# --- Installazione degli Eseguibili ---

install(TARGETS ${ODE_APP_NAME} ${DATA_APP_NAME}
    RUNTIME DESTINATION bin
)