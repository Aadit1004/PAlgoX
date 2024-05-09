cmake_minimum_required(VERSION 3.28)
project(PAlgoX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/palgox_spec.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_library(PAlgoX STATIC src/palgox.cpp)

target_link_libraries(tests PRIVATE PAlgoX)