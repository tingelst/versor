#!/bin/bash

if [[ ! -d build ]]; then
  mkdir -p build/doc
fi

cd build
#cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/osx.cmake .. #or, add toolchain file here
cmake -DBUILD_GRAPHICS=1 ..
make VERBOSE=1 -j3
