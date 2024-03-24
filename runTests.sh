#!/bin/bash
currentDir=$(pwd)
<<<<<<< HEAD
cd $currentDir/Generator/source
mkdir build
cd build
cmake ..
make -j 10
cd $currentDir/Generator/source/build/tests
./tests
=======
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake ..
make -j 10
cd $currentDir/build/test
./CircuitGenTest
>>>>>>> 442514d5a (commit before pull)
