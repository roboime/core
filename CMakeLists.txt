cmake_minimum_required(VERSION 2.8)

project("RoboIME Core 2016")

# set Modules path to find dependencies
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# For YouCompleteMe integration
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Set C++11 as standard compilation
add_definitions("-std=c++11")

include_directories(.)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX -d)

option(BUILD_CLIENTS "ON to build clients. OFF to ignore them." ON)
if (BUILD_CLIENTS)
  add_subdirectory(clients)
endif()

option(BUILD_TESTS "ON to build tests. OFF to ignore them." ON)
if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
