cmake_minimum_required(VERSION 2.8)

include(../cmake/Utils.cmake)

find_package(Protobuf REQUIRED)
require_gtest()
require_gmock()

include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${GMOCK_INCLUDE_DIRS})
include_directories(SYSTEM ${PROTOBUF_INCLUDE_DIRS})
include_directories(SYSTEM ../src)

set(TEST_SRCS
    main.cpp
    #core.cpp
    intel.cpp
)

set(TEST_LIBS
    core
    #interface
)

add_executable(test-roboime-core ${TEST_SRCS})
target_link_libraries(test-roboime-core ${GTEST_BOTH_LIBRARIES} ${GMOCK_LIBRARIES} ${TEST_LIBS})

add_executable(subprocess-repeater subprocess-repeater.cpp)

#target_link_libraries(test-roboime-core ${GTEST_BOTH_LIBRARIES} roboime-core)
#gtest_add_tests(${PROJECT_SOURCE_DIR}/bin/test-roboime-core ""
#    main.cpp
#)

# vim: et sw=4 ts=4
