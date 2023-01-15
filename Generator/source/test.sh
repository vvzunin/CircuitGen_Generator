g++ ./Generators/TruthTable.cpp ./DataBase/DataBaseGenerator.cpp ./Generators/Genetic/Mutations/MutationParameters.cpp ./Generators/Genetic/GeneticParameters.cpp ./Generators/GenerationParameters.cpp Settings.cpp main.cpp -std=c++17 -o prog 2> errors.txt
head -n 17 errors.txt
tail -n 1 errors.txt
