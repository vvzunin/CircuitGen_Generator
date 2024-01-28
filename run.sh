# #!/bin/bash
cd Generator/source
mkdir build
cd build
cmake ..
make -j $(nproc)
cd ../../../
currentDir=$(pwd)
Generator/source/build/circuitgen --json_path=$currentDir/Generator/source/test_data/wast/sample.json
