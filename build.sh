#!/bin/bash
clear;

# check build dir
if [ ! -d build-debug ] 
then 
    mkdir build-debug
fi

# generate cmake files
cmake -B ./build-debug -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CUDA_COMPILER=`which nvcc`

# compile project
cmake --build ./build-debug
#--clean-first

echo compilation completed!
