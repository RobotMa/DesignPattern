cmake_minimum_required(VERSION 3.17)  # CMake version check
project(DesignPattern)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(conan_install)
if (CONAN_INSTALL)
    set(CONAN_PROFILE "focal" CACHE STRING "Use default conan profile")
    conan_install(${CONAN_PROFILE})
endif ()

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
endif ()

#ccache
option(ENABLE_CCACHE "ccache compilation results." ON)
if (ENABLE_CCACHE)
    find_program(CCACHE_COMMAND ccache)
    if (CCACHE_COMMAND)
        list(APPEND CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_COMMAND}")
    else ()
        message(WARNING "ccache not found")
    endif ()
endif ()

add_compile_options(
        -Wall
#        -Werror
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -Wdouble-promotion
        -Wformat=2
)

add_subdirectory(Behavioral)
add_subdirectory(Creational)
add_subdirectory(CRTP)
add_subdirectory(Pimpl)
add_subdirectory(SOLID)
add_subdirectory(Structual)

