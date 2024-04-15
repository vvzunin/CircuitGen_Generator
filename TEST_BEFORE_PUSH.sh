cmake --preset=dev
cmake --build --preset=dev -t format-fix
cmake --build --preset=dev
ctest --preset=dev
