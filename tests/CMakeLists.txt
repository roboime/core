cmake_minimum_required(VERSION 2.8)

include(../cmake/Utils.cmake)

#add_executable(subprocess subprocess.cpp)
#target_link_libraries(subprocess interface)
#add_executable(subprocess-child subprocess-child.cpp)

find_package(Protobuf REQUIRED)
require_gtest()

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${PROTOBUF_INCLUDE_DIRS})
include_directories(SYSTEM ../src)

add_executable(test-roboime-core main.cpp)
target_link_libraries(test-roboime-core ${GTEST_BOTH_LIBRARIES})
#target_link_libraries(test-roboime-core ${GTEST_BOTH_LIBRARIES} roboime-core)
#gtest_add_tests(${PROJECT_SOURCE_DIR}/bin/test-roboime-core ""
#    main.cpp
#)

# vim: et sw=4 ts=4
