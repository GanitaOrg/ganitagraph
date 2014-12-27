##=========================================================================
## This file is part of GanitaGraph software. 
## 
##=========================================================================

project(GanitaGraph CXX C)

## Version
set(GanitaGraph_VERSION_MAJOR "0")
set(GanitaGraph_VERSION_MINOR "3")
set(GanitaGraph_VERSION_PATCH "0")

cmake_minimum_required(VERSION 2.8)

  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wconversion -O3 ${OpenMP_CXX_FLAGS} -msse4")

  enable_testing()

  IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(CPACK_SYSTEM_NAME x86_64)
    set(CPACK_TOPLEVEL_TAG x86_64)
  ELSE (CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(CPACK_SYSTEM_NAME x86_32)
    set(CPACK_TOPLEVEL_TAG x86_32)
  ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")

# configure_file(config.h.in config.h)

include_directories(../src/cpp)
# link_directories (../lib)

add_library(GanitaGraph ../src/cpp/GanitaGraph.cpp ../src/cpp/GanitaTrace.cpp ../src/cpp/GanitaEdge.cpp ../src/cpp/GanitaNode.cpp ../src/cpp/GanitaFormatter.cpp)

target_include_directories (GanitaGraph PUBLIC ../src/cpp)

add_executable(gg2 ../src/drivers/gg2.cc)
add_test(gg2 ../src/drivers/gg2.cc)
add_executable(ganitaGraph ../src/drivers/ganitaGraph.cc)
add_test(ganitaGraph ../src/drivers/ganitaGraph.cc)

target_link_libraries (ganitaGraph LINK_PUBLIC GanitaGraph)
target_link_libraries (gg2 LINK_PUBLIC GanitaGraph)

install(TARGETS ganitaGraph DESTINATION bin)
install(TARGETS GanitaGraph DESTINATION lib)

# if(OpenMP_CXX_FLAGS)
#   set_property(
#     SOURCE hmm_test.cpp
#     PROPERTY COMPILE_DEFINITIONS WITH_OMP
#     )
# ENDIF(OpenMP_CXX_FLAGS)
