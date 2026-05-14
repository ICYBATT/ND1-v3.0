cmake_minimum_required(VERSION 3.15)
project(1UZD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(1UZD
    main.cpp
    studentas.cpp
    FileIO.cpp
    Output.cpp
    NaturalSort.cpp
    Menu.cpp
    Generator.cpp
    Input.cpp
    Tyrimas.cpp
)

target_include_directories(1UZD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

FetchContent_Declare(
    Catch2
    URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.3.zip
)

FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(VectorTests
    tests/VectorTests.cpp
    tests/StudentasVectorTests.cpp
    studentas.cpp
)

target_include_directories(VectorTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(VectorTests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(VectorTests)