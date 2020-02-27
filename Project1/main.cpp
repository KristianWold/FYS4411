#include "src/system.hpp"
#include "src/particles.hpp"
#include "src/InitialStates/initialstate.hpp"
#include "src/InitialStates/randomuniform.hpp"
#include "src/Hamiltonians/hamiltonian.hpp"
#include "src/Hamiltonians/harmonicoscillator.hpp"
#include "src/WaveFunctions/wavefunction.hpp"
#include "src/WaveFunctions/simplegaussian.hpp"
#include "src/WaveFunctions/simplegaussiannumerical.hpp"
#include <iostream>

int main(int argc, char const *argv[]){

    int numPart = atoi(argv[1]);
    int numDim = atoi(argv[2]);
    int numSteps = atoi(argv[3]);

    System* sys = new System();
    sys->setNumParticles(numPart);
    sys->setNumDim(numDim);
    sys->setInitialState(new RandomUniform());
    sys->setWaveFunction(new SimpleGaussian(0.5));
    sys->setHamiltonian(new HarmonicOscillator(1));
    sys->setSeed(42);

    sys->runMetropolis(numSteps);


    return 0;
}
