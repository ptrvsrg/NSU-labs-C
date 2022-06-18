#!/bin/bash

mkdir -p build_$1
cd build_$1
export CTEST_OUTPUT_ON_FAILURE=1

cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DUNLIMITED=ON ../$1
ninja
ninja test

cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DUNLIMITED=OFF ../$1
ninja test
rm -rf *

cmake ../$1 -GNinja -DCMAKE_C_COMPILER=clang -DENABLE_ASAN=true -DUNLIMITED=ON
ninja
ninja test

cmake ../$1 -GNinja -DCMAKE_C_COMPILER=clang -DENABLE_USAN=true -DUNLIMITED=ON
ninja
ninja test

cd ..
rm -rf build_$1
