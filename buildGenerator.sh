#!/bin/bash
cmake -G Ninja -S . -B build "$@"
cmake --build build -j $(nproc)
