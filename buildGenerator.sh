#!/bin/bash
cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release  "$@"
cmake --build build -j $(nproc)
