cmake_minimum_required(VERSION 3.15)

project(1UZD VERSION 3.0.0)

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

add_executable(VectorBenchmark
    VectorBenchmark.cpp
)

target_include_directories(VectorBenchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(StudentuBenchmark
    StudentuBenchmark.cpp
    studentas.cpp
)

target_include_directories(StudentuBenchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

FetchContent_Declare(
    Catch2
    URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.3.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
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

install(TARGETS 1UZD
    RUNTIME DESTINATION .
)

install(TARGETS VectorBenchmark
    RUNTIME DESTINATION tools
)

install(TARGETS StudentuBenchmark
    RUNTIME DESTINATION tools
)

install(FILES README.md
    DESTINATION .
)

install(DIRECTORY docs/html
    DESTINATION docs
    OPTIONAL
)

set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_NAME "ND1-v3.0")
set(CPACK_PACKAGE_VENDOR "VU")
set(CPACK_PACKAGE_CONTACT "Justas Sabeckis")
set(CPACK_PACKAGE_VERSION "3.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Studentu duomenu apdorojimo programa su nuosavu Vector konteineriu")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "VU\\\\Justas-Sabeckis")

set(CPACK_PACKAGE_EXECUTABLES
    "1UZD" "ND1 v3.0"
)

set(CPACK_CREATE_DESKTOP_LINKS
    "1UZD"
)

set(CPACK_NSIS_DISPLAY_NAME "ND1 v3.0")
set(CPACK_NSIS_PACKAGE_NAME "ND1 v3.0")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_MODIFY_PATH OFF)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

set(CPACK_NSIS_DEFINES "RequestExecutionLevel admin")

set(CPACK_NSIS_CREATE_ICONS_EXTRA "
    CreateShortCut '$DESKTOP\\\\ND1 v3.0.lnk' '$INSTDIR\\\\1UZD.exe'
    CreateDirectory '$SMPROGRAMS\\\\VU\\\\Justas-Sabeckis'
    CreateShortCut '$SMPROGRAMS\\\\VU\\\\Justas-Sabeckis\\\\ND1 v3.0.lnk' '$INSTDIR\\\\1UZD.exe'
")

set(CPACK_NSIS_DELETE_ICONS_EXTRA "
    Delete '$DESKTOP\\\\ND1 v3.0.lnk'
    Delete '$SMPROGRAMS\\\\VU\\\\Justas-Sabeckis\\\\ND1 v3.0.lnk'
    RMDir '$SMPROGRAMS\\\\VU\\\\Justas-Sabeckis'
    RMDir '$SMPROGRAMS\\\\VU'
")

include(CPack)