cmake_minimum_required(VERSION 3.0.0)

project(comm)
set(SOURCE_FILES main.cpp)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(LIBS_DIR libs/communication)


add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )


file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "*.h" "*.hh" "*.h++" "*.hxx" "*.H" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.c" "*.cc" "*.c++" "*.cxx" "*.C" "*.cpp")

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

include(CPack)

