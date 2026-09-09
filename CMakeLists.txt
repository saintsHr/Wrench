cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Wrench VERSION 0.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
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
find_package(OpenGL REQUIRED)

# --- Engine Build ---

add_library(Wrench STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/core/engine.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/window/window.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/renderer/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/renderer/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/renderer/mesh.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/utils/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wrench/utils/timer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/src/glad.c
)

add_library(Wrench::Wrench ALIAS Wrench)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/src/glad.c

    PROPERTIES COMPILE_OPTIONS "-w"
)

target_include_directories(Wrench PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(Wrench SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
)

target_link_libraries(Wrench PUBLIC
    glfw
    OpenGL::GL
)

# ================================================================
# Compiler Options
# ================================================================

# Common debug

target_compile_options(Wrench PRIVATE
    $<$<CONFIG:Debug>:
        -g3
        -O0

        -Werror

        -fno-omit-frame-pointer
        -fno-inline
        -fstack-protector-all

        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
        -Wimplicit-fallthrough
        -Wcast-align
        -Wcast-qual
        -Wstrict-aliasing
        
        $<$<COMPILE_LANGUAGE:CXX>:
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
        >
    >
)

# GCC debug

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Wrench PRIVATE
        $<$<CONFIG:Debug>:
            $<$<COMPILE_LANGUAGE:CXX>:
                -Wuseless-cast
            >
        >
    )
endif()

# Clang debug

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(Wrench PRIVATE
        $<$<CONFIG:Debug>:
            $<$<COMPILE_LANGUAGE:CXX>:
                
            >
        >
    )
endif()

# Common release

target_compile_options(Wrench PRIVATE
    $<$<CONFIG:Release>:
        -O3

        -DNDEBUG

        -g0

        -funroll-loops
        -ffunction-sections
        -fno-omit-frame-pointer
        -fvisibility=hidden
        -fdata-sections
    >
)

# GCC release

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Wrench PRIVATE
        $<$<CONFIG:Release>:
            
        >
    )
endif()

# Clang release

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(Wrench PRIVATE
        $<$<CONFIG:Release>:
            
        >
    )
endif()

# ================================================================
# Linker Options
# ================================================================

# Common debug

target_link_options(Wrench PRIVATE
    $<$<CONFIG:Debug>:
        
    >
)

# Common Release

target_link_options(Wrench PRIVATE
    $<$<CONFIG:Release>:
        
    >
)

# GCC debug

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(Wrench PRIVATE
        $<$<CONFIG:Debug>:
            
        >
    )
endif()

# Clang debug

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_options(Wrench PRIVATE
        $<$<CONFIG:Debug>:
            
        >
    )
endif()


# GCC release

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(Wrench PRIVATE
        $<$<CONFIG:Release>:
            
        >
    )
endif()

# Clang release

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_options(Wrench PRIVATE
        $<$<CONFIG:Release>:
            
        >
    )
endif()

# --- compile_commands.json Copy & Move ---

add_custom_target(copy_compile_commands ALL
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
)

# --- Install Rules ---

install(TARGETS Wrench
    EXPORT WrenchTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/wrench
    DESTINATION include
)

install(EXPORT WrenchTargets
    FILE WrenchTargets.cmake
    NAMESPACE Wrench::
    DESTINATION lib/cmake/Wrench
)

# --- Package Config ---

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/WrenchConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/WrenchConfig.cmake
    INSTALL_DESTINATION lib/cmake/Wrench
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/WrenchConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/WrenchConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/WrenchConfigVersion.cmake
    DESTINATION lib/cmake/Wrench
)