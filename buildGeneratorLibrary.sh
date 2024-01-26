#!/bin/bash
cd Generator/source
mkdir build
cd build
cmake ..
cmake --build . --target cgen
cp libcgen.so ../../../libcgen.so
cd ../../../