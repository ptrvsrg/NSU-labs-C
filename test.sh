#!/bin/bash

NORMAL='\033[0m'
YELLOW='\033[1;33m'

mkdir -p build_$1
cd build_$1
export CTEST_OUTPUT_ON_FAILURE=1

cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DUNLIMITED=ON ../$1
ninja
ninja test
echo "${YELLOW} in.txt ${NORMAL}"
head -c 256 in.txt
echo "\n${YELLOW} out.txt ${NORMAL}"
head -c 256 out.txt
echo "\n"
rm -rf *

cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DUNLIMITED=OFF ../$1
ninja
ninja test
echo "${YELLOW} in.txt ${NORMAL}"
head -c 256 in.txt
echo "\n${YELLOW} out.txt ${NORMAL}"
head -c 256 out.txt
echo "\n"
rm -rf *

cmake ../$1 -GNinja -DCMAKE_C_COMPILER=clang -DENABLE_ASAN=true -DUNLIMITED=ON
ninja
ninja test
echo "${YELLOW} in.txt ${NORMAL}"
head -c 256 in.txt
echo "\n${YELLOW} out.txt ${NORMAL}"
head -c 256 out.txt
echo "\n"
rm -rf *

cmake ../$1 -GNinja -DCMAKE_C_COMPILER=clang -DENABLE_USAN=true -DUNLIMITED=ON
ninja
ninja test
echo "${YELLOW} in.txt ${NORMAL}"
head -c 256 in.txt
echo "\n${YELLOW} out.txt ${NORMAL}"
head -c 256 out.txt
echo "\n"
rm -rf *

cd ..
rm -rf build_$1
