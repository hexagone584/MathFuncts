#guarantees compatibility
cmake_minimum_required(VERSION 3.23)

#Basically tells CMake that after this command, the rest describes a description of the software project of a given name (I have it as MathFuncts for this case)
#Under the hood, it checks if the environment is actually able to build the software
project(MathFuncts)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MathFuncts main.cpp)