cmake_minimum_required(VERSION 2.8.10)

project(roboime-core)
set(DESCRIPTION "RoboIME Core 2016")

# set Modules path to find dependencies
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# For YouCompleteMe integration
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Super strict warnings =)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -pedantic-errors ${CMAKE_CXX_FLAGS}")

include(${PROJECT_SOURCE_DIR}/cmake/Utils.cmake)
# Set C++11 as standard compilation
require_cxx11()

# Threads
find_package(Threads REQUIRED)

# Protobuf
find_package(Protobuf REQUIRED)
include_directories(SYSTEM ${PROTOBUF_INCLUDE_DIRS})

protobuf_generate_cpp(PROTO_CPP PROTO_H
    protos/messages_robocup_ssl_detection.proto
    protos/messages_robocup_ssl_geometry.proto
    protos/messages_robocup_ssl_wrapper.proto
    protos/messages_robocup_ssl_refbox_log.proto
    protos/grSim_Replacement.proto
    protos/grSim_Commands.proto
    protos/grSim_Packet.proto
)

include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX -d)

add_subdirectory(src)

option(BUILD_CLIENTS "ON to build clients. OFF to ignore them." ON)
if (BUILD_CLIENTS)
  add_subdirectory(clients)
endif()

option(BUILD_TESTS "ON to build tests. OFF to ignore them." ON)
if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
