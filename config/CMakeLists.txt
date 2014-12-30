##=========================================================================
## This file is part of GanitaGraph software. 
## 
##=========================================================================

project(GanitaGraph CXX C)

## Version
set(GanitaGraph_VERSION_MAJOR "0")
set(GanitaGraph_VERSION_MINOR "3")
set(GanitaGraph_VERSION_PATCH "2")

cmake_minimum_required(VERSION 2.8)

  enable_testing()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "CC")
  set(warnings "-Wall -Wextra")
  set(cmake_cxx_extra "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(warnings "-Wall -Wextra")
  set(cmake_cxx_extra "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(warnings "-Wall -Wextra")
  set(cmake_cxx_extra "-stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang++")
  set(warnings "-Wall -Wextra")
  set(cmake_cxx_extra "-stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "clang++")
  set(warnings "-Wall -Wextra")
  set(cmake_cxx_extra "-stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(warnings "/W4 /WX /EHsc")
else()
  set(warnings "-Wall -Wextra")
  set(cmake_cxx_extra "-std=c++11")
endif()

if (NOT CONFIGURED_ONCE)
  set(CMAKE_CXX_FLAGS "${warnings} ${cmake_cxx_extra}"
    CACHE STRING "Flags used by the compiler during build." FORCE)
  set(CMAKE_C_FLAGS "${warnings} ${cmake_cxx_extra}"
    CACHE STRING "Flags used by the compiler during build." FORCE)
endif()

  IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(CPACK_SYSTEM_NAME x86_64)
    set(CPACK_TOPLEVEL_TAG x86_64)
  ELSE (CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(CPACK_SYSTEM_NAME x86_32)
    set(CPACK_TOPLEVEL_TAG x86_32)
  ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")

# configure_file(config.h.in config.h)

include_directories(../src/include)

add_library(GanitaGraph ../src/cpp/GanitaGraph.cpp ../src/cpp/GanitaTrace.cpp ../src/cpp/GanitaEdge.cpp ../src/cpp/GanitaNode.cpp ../src/cpp/GanitaFormatter.cpp)

target_include_directories (GanitaGraph PUBLIC ../src/cpp)

add_executable(ganitagraph2 ../src/drivers/gg2.cc)
add_executable(ganitagraph1 ../src/drivers/gg1.cc)

target_link_libraries (ganitagraph1 LINK_PUBLIC GanitaGraph m)
target_link_libraries (ganitagraph2 LINK_PUBLIC GanitaGraph m)

install(TARGETS ganitagraph1 DESTINATION bin)
install(TARGETS ganitagraph2 DESTINATION bin)
install(TARGETS GanitaGraph DESTINATION lib)
FILE(GLOB files "../src/include/ganita/graph/*")
install(FILES ${files} DESTINATION include/ganita/graph)

# if(OpenMP_CXX_FLAGS)
#   set_property(
#     SOURCE hmm_test.cpp
#     PROPERTY COMPILE_DEFINITIONS WITH_OMP
#     )
# ENDIF(OpenMP_CXX_FLAGS)
