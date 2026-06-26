cmake_minimum_required(VERSION 3.16)

file(READ "${CMAKE_SOURCE_DIR}/VERSION" HELIUM_VERSION)
string(STRIP "${HELIUM_VERSION}" HELIUM_VERSION)

project(Helium
    VERSION ${HELIUM_VERSION}
    LANGUAGES C
)

configure_file(
    "${CMAKE_SOURCE_DIR}/version.h.in"
    "${CMAKE_BINARY_DIR}/generated/include/version.h"
    @ONLY
)



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

function(setup_helium_target target)
    target_include_directories(${target} PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${CMAKE_BINARY_DIR}/generated/include"
    )
endfunction()

setup_helium_target(helium)
setup_helium_target(debug)
setup_helium_target(profiler)

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