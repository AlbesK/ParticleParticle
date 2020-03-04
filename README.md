# ParticleParticle
Benchmark numerical model based on particle-particle electrostatic interactions written in C and in object oriented C++.
This was one of the 2 numerical methods used for my dissertation on calculating the inverse square law for electric charges rapidly with complexity O(n<sup>2</sup>).

## Theory

<img src="https://github.com/AlbesK/ParticleParticle/blob/master/force.png" alt="Electric Force" width=80%/>

For a system of N charges in space as shown in the figure above and the equation shown within it for the PP model force calculation approach can be used to calculate the inverse square law force for gravitational or electrostatic interactions for every pair and aggregate the forces for each particle with respect to all others. This direct sum method can be applied for potentials and energies in the system with similar working behaviour and scale as O(n<sup>2</sup>).

## Usage

Both Src and Src_C++ have makefiles to be executed by make after that run main.c or main.cpp accordingly. 

## Memory check:

if you have [valgrind](https://valgrind.org/) installed to check efficiency of this build in heap by typing:

"valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes main.o" or however the output file is saved.
