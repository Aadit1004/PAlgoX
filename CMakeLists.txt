cmake_minimum_required(VERSION 3.28)
project(PAlgoX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

find_package(OpenMP REQUIRED)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(tests tests/palgox_spec.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_library(PAlgoX STATIC src/palgox.cpp)

# Link OpenMP libraries
target_link_libraries(PAlgoX PRIVATE OpenMP::OpenMP_CXX)

target_link_libraries(tests PRIVATE PAlgoX)

add_executable(speedup_tests tests/speedup_tests.cpp)

target_link_libraries(speedup_tests PRIVATE PAlgoX)
