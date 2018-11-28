cmake_minimum_required(VERSION 3.6)
project(eternal LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(eternal INTERFACE)
target_include_directories(eternal SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/include)

option(WITH_TESTS "Enable tests" ON)
if (WITH_TESTS)
    add_subdirectory(test)
endif()
