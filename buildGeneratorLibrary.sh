#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake ..
cmake --build . --target cgen
cp libcgen.so ../libcgen.so
cd ../