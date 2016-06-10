

cmake_minimum_required(VERSION 2.8.9)


#EXEC = waveguide

#TARGET1 = main
#TARGET2 = ProblemFormulate
#TARGET3 = Mesh  # this class requires the Colsamm library files
#TARGET4 = Vertex
#TARGET5 = Face

# Defining the project name
project (SiWiR2_FEM)

set(CMAKE_CXX_FLAGS "-Wall -Winline -Wshadow -pedantic")

add_definitions(-std=c++11)

# Bringing in the include directories
include_directories( include_colsamm include)


#Adding the sources using the set command
set(SOURCES test/main.cpp src/ProblemFormulate.cpp src/Mesh.cpp src/Vertex.cpp src/Face.cpp src/Vector.cpp src/Matrix.cpp)   # No need for Solver.cpp

#Setting the executable file
add_executable(waveguide ${SOURCES})



