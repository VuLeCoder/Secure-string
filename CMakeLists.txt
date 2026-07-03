cmake_minimum_required(VERSION 3.10)

project(Secure-Memory)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
)

# Header files (optional, but helpful for IDEs)
set(HEADERS
    include/allocator/SecureAllocator.h
    include/allocator/SecureMemory.h
)

# Create executable
add_executable(secure-memory ${SOURCES} ${HEADERS})