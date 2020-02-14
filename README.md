# ParticleParticle
Benchmark numerical model based on particle-particle electrostatic interactions written in C and in object oriented C++.
This was one of the 2 numerical methods used for my dissertation on calculating the inverse square law for electric charges rapidly using this model as a benchmark with complexity O(n<sup>2</sup>).

## Usage

Both Src and Src_C++ have makefiles to be executed by make after that run main.c or main.cpp accordingly. 

## Memory check:

if you have [valgrind](https://valgrind.org/) installed to check efficiency of this build in heap by typing:

"valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./td"
