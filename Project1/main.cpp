#include "src/system.hpp"
#include "src/particles.hpp"
#include "src/sampler.hpp"
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
    double stepLength = atof(argv[4]);
    double alpha = atof(argv[5]);

    System* sys = new System();

    sys->setStepLength(stepLength);
    sys->setNumParticles(numPart);
    sys->setNumDim(numDim);
    sys->setInitialState(new RandomUniform());
    sys->setWaveFunction(new SimpleGaussian(alpha));
    sys->setHamiltonian(new HarmonicOscillator(1));
    sys->setSampler(new Sampler());
    sys->setMetropolisSteps(numSteps);
    sys->setSeed(39);

    sys->runMetropolis();

    return 0;
}
