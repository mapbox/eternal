set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fno-rtti -fno-exceptions")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()

add_executable(test-map map.test.cpp)
target_link_libraries(test-map PUBLIC eternal)

option(WITH_BENCHMARKS "Enable benchmarks" ON)
if (WITH_BENCHMARKS)
    execute_process(
        COMMAND git submodule update --init vendor/benchmark
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    add_custom_target(
        update-benchmark ALL
        COMMAND git submodule update --init vendor/benchmark
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        COMMENT "Updating submodules..."
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Don't enable tests")
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Don't use GTest")
    set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "Don't use exceptions")
    add_subdirectory(../vendor/benchmark ${CMAKE_BINARY_DIR}/benchmark)

    add_executable(benchmark-map map.benchmark.cpp)
    target_link_libraries(benchmark-map PUBLIC eternal benchmark)
endif()