cmake_minimum_required(VERSION 3.5)

project (scheme)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/syntax.cpp
    ${PROJECT_SOURCE_DIR}/src/RE.cpp
    ${PROJECT_SOURCE_DIR}/src/parser.cpp
    ${PROJECT_SOURCE_DIR}/src/expr.cpp
    ${PROJECT_SOURCE_DIR}/src/value.cpp
    ${PROJECT_SOURCE_DIR}/src/evaluation.cpp
    ${PROJECT_SOURCE_DIR}/src/Def.cpp
)

add_executable(myscheme ${SOURCES})

target_compile_options(myscheme
  PRIVATE
    -g
)
