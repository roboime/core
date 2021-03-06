# Some utilities
#TODO: comment/document

macro(standard_paths ARG0 ARG1 ARG2)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ARG0}/${ARG1})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ARG0}/${ARG2})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARG0}/${ARG2})
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    endforeach()
    set(CMAKE_DEBUG_POSTFIX d)
    set(CMAKE_MINSIZEREL_POSTFIX min)
endmacro()

macro(standard_config)
    set(CMAKE_AUTOMOC YES)
    set(CMAKE_INCLUDE_CURRENT_DIR YES)
endmacro()

macro(require_cxx14)
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
  check_cxx_compiler_flag("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
  if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
  elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
  else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14/C++1y support, which is required.")
  endif()
endmacro()

macro(require_cxx11)
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
  check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0Y)
  if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
  elseif(COMPILER_SUPPORTS_CXX0Y)
    set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
  else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11/C++0x support, which is required.")
  endif()
endmacro()

macro(require_gnucxx11)
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("-std=gnu++11" COMPILER_SUPPORTS_CXX11)
  check_cxx_compiler_flag("-std=gnu++0x" COMPILER_SUPPORTS_CXX0Y)
  if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
  elseif(COMPILER_SUPPORTS_CXX0Y)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x ${CMAKE_CXX_FLAGS}")
  else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no GNU C++11/C++0x support, which is required.")
  endif()
endmacro()

macro(require_c11)
  include(CheckCCompilerFlag)
  check_c_compiler_flag("-std=c11" COMPILER_SUPPORTS_C11)
  check_c_compiler_flag("-std=c1x" COMPILER_SUPPORTS_C1X)
  if(COMPILER_SUPPORTS_C11)
    set(CMAKE_C_FLAGS "-std=c11 ${CMAKE_C_FLAGS}")
  elseif(COMPILER_SUPPORTS_C1X)
    set(CMAKE_C_FLAGS "-std=c1x ${CMAKE_C_FLAGS}")
  else()
    message(STATUS "The compiler ${CMAKE_C_COMPILER} has no C11/C1x support, which is required.")
  endif()
endmacro()

macro(require_c99)
  include(CheckCCompilerFlag)
  check_c_compiler_flag("-std=c99" COMPILER_SUPPORTS_C99)
  if(COMPILER_SUPPORTS_C99)
    set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
  else()
    message(STATUS "The compiler ${CMAKE_C_COMPILER} has no C99 support, which is required.")
  endif()
endmacro()

macro(require_gtest)
  include(ExternalProject)

  externalproject_add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.7.0
    # Disable install step
    INSTALL_COMMAND ""
  )

  externalproject_get_property(googletest source_dir)
  externalproject_get_property(googletest binary_dir)

  set(GTEST_INCLUDE_DIRS ${source_dir}/include)
  set(GTEST_LIBRARY_PATH ${binary_dir})

  # TODO: correct suffix for other platforms
  #set(GTEST_LIBRARY ${GTEST_LIBRARY_PATH}/gtest.a)
  set(GTEST_LIBRARY gtest)
  add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
  set_property(
    TARGET ${GTEST_LIBRARY}
    PROPERTY IMPORTED_LOCATION
    ${GTEST_LIBRARY_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  )
  add_dependencies(${GTEST_LIBRARY} googletest)

  #set(GTEST_MAIN_LIBRARY ${GTEST_LIBRARY_PATH}/gtest-main.a)
  set(GTEST_MAIN_LIBRARY gtest-main)
  add_library(${GTEST_MAIN_LIBRARY} UNKNOWN IMPORTED)
  set_property(
    TARGET ${GTEST_MAIN_LIBRARY}
    PROPERTY IMPORTED_LOCATION
    ${GTEST_LIBRARY_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
  )
  add_dependencies(${GTEST_MAIN_LIBRARY} googletest)

  find_package(Threads)
  set(GTEST_LIBRARIES ${GTEST_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
  set(GTEST_MAIN_LIBRARIES ${GTEST_MAIN_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
  set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
endmacro()

# vim: et sw=2 ts=2 sts=2
