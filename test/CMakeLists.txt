cmake_minimum_required(VERSION 3.10.2)
project(CircuitGenTest VERSION 0.0.0)

include(ExternalProject)
include(FetchContent)

# Get googletest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} 
  AuxiliaryMethodsTests.cpp 
  SettingsTests.cpp 
  TruthTableTests.cpp 
  OrientedGraphTests.cpp 
  OrientedGraphSysTests.cpp 
  FilesToolsTests.cpp 
  GraphVertexTests.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
AuxiliaryMethods 
Circuit 
Reliability 
TruthTable 
OrientedGraph 
GeneticParameters
MutationParameters 
RecombinationParameters 
SelectionParameters 
ParentsParameters 
GraphVertex 
FilesTools 
Settings 
OptimizationUtils 
ThreadPool 

nlohmann_json::nlohmann_json
gtest
gtest_main
)
