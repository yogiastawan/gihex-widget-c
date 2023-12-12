cmake_minimum_required(VERSION 3.0.0...3.5.0)
project(gihex-widget VERSION 0.1.0 LANGUAGES C)

set(C_STANDARD 11)

include(CTest)
enable_testing()

option(BUILD_EXAMPLES "Build example file" ON)
option(BUILD_SHARED "Build example file" OFF)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

include_directories(src)

add_subdirectory(src)
add_subdirectory(examples)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
