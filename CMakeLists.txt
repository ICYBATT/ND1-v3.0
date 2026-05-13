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