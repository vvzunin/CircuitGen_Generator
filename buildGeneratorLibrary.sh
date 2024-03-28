#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake ..
cmake --build . --target cgen
cp src/libcgen.so ../libcgen.so
cd ../