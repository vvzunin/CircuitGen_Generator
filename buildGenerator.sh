#!/bin/bash
cd Generator/source
mkdir build
cd build
cmake ..
make -j 10
cd ../../../