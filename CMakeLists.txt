cmake_minimum_required(VERSION 3.16)

project(Helium C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(helium ${SOURCES})
add_executable(debug ${SOURCES})

set_target_properties(helium PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

set_target_properties(debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

target_include_directories(helium PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(debug PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

if(MSVC)
    target_compile_options(helium PRIVATE /O2)
    target_compile_options(debug PRIVATE /O2)
else()
    target_compile_options(helium PRIVATE -O3)
    target_compile_options(debug PRIVATE -O3)
endif()

target_compile_definitions(debug PRIVATE
    HELIUM_DEBUG
)