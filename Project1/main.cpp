#include "src/system.hpp"
#include "src/particles.hpp"
#include "src/sampler.hpp"
#include "src/InitialStates/initialstate.hpp"
#include "src/InitialStates/randomuniform.hpp"
#include "src/InitialStates/initialhardshell.hpp"
#include "src/Hamiltonians/hamiltonian.hpp"
#include "src/Hamiltonians/harmonicoscillator.hpp"
#include "src/WaveFunctions/wavefunction.hpp"
#include "src/WaveFunctions/simplegaussian.hpp"
#include "src/WaveFunctions/simplegaussiannumerical.hpp"
#include "src/WaveFunctions/hardshell.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]){

    std::string directory = argv[1];
    std::string thread = argv[2];
    int numPart = atoi(argv[3]);
    int numDim = atoi(argv[4]);
    int numSteps = atoi(argv[5]);
    double stepLength = atof(argv[6]);
    double alpha = atof(argv[7]);
    double a = atof(argv[8]);
    double omega = atof(argv[9]);

    System* sys = new System();

    sys->setDirectory(directory);
    sys->setThread(thread);

    sys->setStepLength(stepLength);
    sys->setNumParticles(numPart);
    sys->setNumDim(numDim);

    sys->setInitialState(new InitialHardshell());
    sys->setWaveFunction(new Hardshell(alpha, a));
    sys->setHamiltonian(new HarmonicOscillator(omega));
    sys->setSampler(new Sampler());
    sys->setMetropolisSteps(numSteps);
    sys->setSeed(42 + atoi(argv[2]) - 1);

    sys->runMetropolis();
    return 0;
}
