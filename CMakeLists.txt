cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(wrench VERSION 0.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_INCLUDE_NONE ON)

# --- Dependencies ---

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    message(STATUS "Compile Cache Enabled (${CCACHE_PROGRAM})")

    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

include(CMakePackageConfigHelpers)
find_package(glfw3 REQUIRED)

# --- Engine Build ---

add_library(wrench STATIC
    src/wrench/core/engine.cpp

    src/wrench/window/window.cpp

    src/wrench/renderer/renderer.cpp
    src/wrench/renderer/shader.cpp
    src/wrench/renderer/mesh.cpp

    third_party/src/glad.c
)

set_source_files_properties(
    third_party/src/glad.c

    PROPERTIES COMPILE_OPTIONS "-w"
)

target_include_directories(wrench PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(wrench SYSTEM PRIVATE
    third_party/include
)

target_link_libraries(wrench PRIVATE
    glfw
)

target_compile_options(wrench PRIVATE
    $<$<CONFIG:Debug>:
        -g3 -O0 -DWRENCH_DEBUG -Werror
        -fno-omit-frame-pointer -fno-inline
        -fstack-protector-all -Wall -Wextra
        -Wpedantic -Wshadow -Wconversion
        -Wsign-conversion -Wnull-dereference
        -Wdouble-promotion -fsanitize=address,undefined,leak
        -fsanitize-address-use-after-scope

        $<$<COMPILE_LANGUAGE:CXX>:
            -Wnon-virtual-dtor
            -Wold-style-cast
        >
    >
    $<$<CONFIG:Release>:
        -O3 -DNDEBUG -g0 -fomit-frame-pointer
        -flto -funroll-loops -fmerge-all-constants
        -fno-stack-protector -DWRENCH_RELEASE
    >
)
target_link_options(wrench PUBLIC
    $<$<CONFIG:Debug>:-fsanitize=address,undefined,leak>
    $<$<CONFIG:Release>:-flto -s>
)

# --- Install Rules ---

install(TARGETS wrench
    EXPORT wrenchTargets
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/wrench
    DESTINATION include
)

install(EXPORT wrenchTargets
    FILE wrenchTargets.cmake
    NAMESPACE wrench::
    DESTINATION lib/cmake/wrench
)

# --- Version Rules ---

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/wrenchConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/wrenchConfig.cmake
    INSTALL_DESTINATION lib/cmake/wrench
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/wrenchConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/wrenchConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/wrenchConfigVersion.cmake
    DESTINATION lib/cmake/wrench
)