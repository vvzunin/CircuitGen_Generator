#!/bin/bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_OPTIMIZATIONS_GEN=ON
cmake --build build -j $(nproc)