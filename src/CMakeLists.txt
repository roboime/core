#add_subdirectory(control)
add_subdirectory(interface)
add_subdirectory(utils)

set(CORE_SRCS
  core.cpp
  intel.cpp)

add_library(core ${CORE_SRCS})
target_link_libraries(core interface ${CMAKE_THREAD_LIBS_INIT})
