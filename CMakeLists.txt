cmake_minimum_required(VERSION 3.10)
project(CSEC C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/.hashdll
)

# Setup hash dll
set(HASHDLL_SOURCES .hashdll/hash.cpp)
set(HASHDLL_HEADERS .hashdll/hash.h)
add_library(hash SHARED ${HASHDLL_SOURCES} ${HASHDLL_HEADERS})

set_target_properties(hash PROPERTIES
    PREFIX ""
    OUTPUT_NAME "hash"
)
target_compile_definitions(hash PRIVATE HASHDLL_EXPORTS)

# Glob src files
file(GLOB SOURCES "src/*.c")

# Create program executable
add_executable(main ${SOURCES})

# include libraries
target_link_libraries(main kernel32)
