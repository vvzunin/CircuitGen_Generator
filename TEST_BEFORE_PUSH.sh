cmake --preset=dev
cmake --build --preset=dev -t format-fix  -j $(nproc)
cmake --build --preset=dev -j $(nproc)
ctest --preset=dev
