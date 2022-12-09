cmake_minimum_required(VERSION 3.20)
project(structures1)

set(CMAKE_CXX_STANDARD 14)

add_executable(structures1 main.cpp wet1util.h AVLTree.cpp AVLTree.h Player.cpp Player.h Team.cpp Team.h Functors.cpp Functors.h worldcup2a2.cpp worldcup2a2.h)
