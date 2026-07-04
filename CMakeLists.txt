cmake_minimum_required(VERSION 3.10)

project(
    SecureString
    VERSION 0.1.0
    DESCRIPTION "Secure C++ string library"
    LANGUAGES CXX
)

# ======================================================================
# Options
# ======================================================================

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# ======================================================================
# C++
# ======================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ======================================================================
# Library
# ======================================================================

add_library(SecureAllocator src/allocator/SecureMemory.cpp)
target_include_directories(SecureAllocator PUBLIC ${PROJECT_SOURCE_DIR}/include/allocator)

# add_library(SecureString
#     src/string/...
# )
# target_include_directories(SecureString PUBLIC ${PROJECT_SOURCE_DIR}/include/string)

# ======================================================================
# Tests
# ======================================================================

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
