#!/bin/bash
clear;

# check build dir
if [ ! -d build ] 
then 
    mkdir build 
fi

# generate cmake files
cmake -B ./build -S . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CUDA_COMPILER=`which nvcc`

# compile project
cmake --build ./build 
#--clean-first

echo compilation completed!
