message(STATUS "\n\n----- MiniZinc build configuration ----")
if(BUILD_REF)
  set(STR_BUILD_REF "build ${BUILD_REF}")
endif()
message(STATUS "MiniZinc version: ${libminizinc_VERSION} ${STR_BUILD_REF}")
message(STATUS "Enabled drivers:")

if(TARGET minizinc_cplex)
  if(CPLEX_PLUGIN)
    set(STR_CPLEX_PLUGIN " PLUGIN")
  endif()
  message(STATUS "\tCPLEX${STR_CPLEX_PLUGIN}: ${CPLEX_INCLUDE_DIRS}")
endif()
if(TARGET minizinc_gecode)
  message(STATUS "\tGecode: ${GECODE_INCLUDE_DIRS}")
endif()
if(TARGET minizinc_gurobi)
  if(GUROBI_PLUGIN)
    set(STR_GUROBI_PLUGIN " PLUGIN")
  endif()
  message(STATUS "\tGurobi${STR_GUROBI_PLUGIN}: ${GUROBI_INCLUDE_DIRS}")
endif()
if(TARGET minizinc_osicbc)
  message(STATUS "\tOSICBC: ${OSICBC_INCLUDE_DIRS}")
endif()
if(TARGET minizinc_scip)
  message(STATUS "\tOSICBC: ${SCIP_INCLUDE_DIRS}")
endif()
if(TARGET minizinc_xpress)
  message(STATUS "\tOSICBC: ${XPRESS_INCLUDE_DIRS}")
endif()
message(STATUS "---------------------------\n\n")