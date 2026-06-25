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
add_executable(profiler ${SOURCES})

set_target_properties(helium PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

set_target_properties(debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

set_target_properties(profiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

target_include_directories(helium PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(debug PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(profiler PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

if(MSVC)
    target_compile_options(helium PRIVATE /O2 /GL)
    target_compile_options(debug PRIVATE /O2 /GL)

    target_link_options(helium PRIVATE /LTCG)
    target_link_options(debug PRIVATE /LTCG)

    message(WARNING "gprof profiling is not supported on MSVC")
else()
    target_compile_options(helium PRIVATE
        -O3
        -march=native
        -flto
        -falign-functions=32
        -falign-loops=32
        -fno-tree-vectorize
    )

    target_compile_options(debug PRIVATE
        -O3
        -march=native
        -flto
    )

    target_compile_options(profiler PRIVATE
        -pg
        -g
        -O0
    )

    target_link_options(helium PRIVATE
        -flto
    )

    target_link_options(debug PRIVATE
        -flto
    )

    target_link_options(profiler PRIVATE
        -pg
    )
endif()

target_compile_definitions(debug PRIVATE
    HELIUM_DEBUG
)