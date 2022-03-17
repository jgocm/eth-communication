cmake_minimum_required(VERSION 3.0.0)

project(comm)
set(SOURCE_FILES main.cpp)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(LIBS_DIR libs/communication)

include_directories( ${LIBS_DIR} )
link_directories( ${LIBS_DIR} )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

target_link_libraries( ${PROJECT_NAME} ${LIBS_DIR} )

include(CPack)

