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

# protobuf stuff
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

file (GLOB COMMOM_PROTO "proto/*.proto")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${COMMOM_PROTO})

add_executable(net utils/net.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(net ${PROTOBUF_LIBRARIES})
set_target_properties(net PROPERTIES COMPILE_FLAGS "-DRCVR")

add_executable(core core.cpp)

option(BUILD_TESTS "ON to build tests. OFF to ignore them." ON)
if (BUILD_TESTS)
  add_subdirectory(tests)
endif()
