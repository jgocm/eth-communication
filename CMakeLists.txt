cmake_minimum_required(VERSION 3.0.0)
project(comm)

include(CTest)
enable_testing()

add_executable(comm main.cpp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

