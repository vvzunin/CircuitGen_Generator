#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build -j $(nproc)