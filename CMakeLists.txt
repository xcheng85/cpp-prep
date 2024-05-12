cmake_minimum_required(VERSION 3.29)
project(CPP_PREP LANGUAGES CUDA CXX VERSION 1.0.0 )
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#include cmake script
include(CHECK_INSOURCE_BUILD)
include(BOOST)
include(CUDA)

# c++ version
set(CMAKE_CXX_STANDARD 23)
# for experimental/future
#GCC provides experimental support for the upcoming ISO C++ standard, C++0x. 
#This support can be enabled with the -std=c++0x or -std=gnu++0x compiler options; 
#the former disables GNU extensions.
set(CMAKE_CXX_FLAGS "-std=c++0x -lstdc++fs")

add_subdirectory(src bin)

add_subdirectory(test)