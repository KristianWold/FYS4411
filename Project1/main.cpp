#include "src/system.hpp"
#include "src/particles.hpp"
#include "src/sampler.hpp"
#include "src/InitialStates/initialstate.hpp"
#include "src/InitialStates/randomuniform.hpp"
#include "src/InitialStates/initialhardshell.hpp"
#include "src/Hamiltonians/hamiltonian.hpp"
#include "src/Hamiltonians/harmonicoscillator.hpp"
#include "src/Hamiltonians/ellipticaloscillator.hpp"
#include "src/WaveFunctions/wavefunction.hpp"
#include "src/WaveFunctions/simplegaussian.hpp"
#include "src/WaveFunctions/simplegaussiannumerical.hpp"
#include "src/WaveFunctions/hardshell.hpp"
#include "src/WaveFunctions/ellipticalhardshell.hpp"
#include <iostream>
#include <string>

void initiateSystemObjects(
    InitialState* &initialstate,
    WaveFunction* &wavefunction,
    Hamiltonian* &hamiltonian,
    char const *argv[])
{
    double alpha = atof(argv[8]);
    double a = atof(argv[9]);
    double omega = atof(argv[10]);

    switch(atoi(argv[11]))
    {
        case 1:
            initialstate = new RandomUniform();
            break;
        case 2:
            initialstate = new InitialHardshell();
            break;
        default:
            std::cout << "ost1" << std::endl;
    }

    switch(atoi(argv[12]))
    {
        case 1:
            wavefunction = new SimpleGaussian(alpha);
            break;
        case 2:
            wavefunction = new SimpleGaussianNumerical(alpha, 1e-4);
            break;
        case 3:
            wavefunction = new Hardshell(alpha, a);
            break;
        case 4:
            wavefunction = new EllipticalHardshell(alpha, a, 2.82843);
            break;
        default:
            std::cout << "ost2" << std::endl;
    }

    switch(atoi(argv[13]))
    {
        case 1:
            hamiltonian = new HarmonicOscillator(omega);
            break;
        case 2:
            hamiltonian = new EllipticalOscillator(2.82843);
            break;
        default:
            std::cout << "ost3" << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::string directory = argv[1];
    std::string thread = argv[2];
    int numPart = atoi(argv[3]);
    int numDim = atoi(argv[4]);
    int numSteps = atoi(argv[5]);
    double stepLength = atof(argv[6]);
    int importanceSampling = atoi(argv[7]);

    InitialState* initialState;
    WaveFunction* wavefunction;
    Hamiltonian* hamiltonian;

    initiateSystemObjects(
        initialState,
        wavefunction,
        hamiltonian,
        argv
    );

    System* sys = new System();
    sys->setDirectory(directory);
    sys->setThread(thread);

    sys->setNumParticles(numPart);
    sys->setNumDim(numDim);
    sys->setMetropolisSteps(numSteps);
    sys->setStepLength(stepLength);
    sys->setImportanceSampling(importanceSampling);
    sys->setSeed(42 + atoi(argv[2]) - 1);

    sys->setInitialState(initialState);
    sys->setWaveFunction(wavefunction);
    sys->setHamiltonian(hamiltonian);
    sys->setSampler(new Sampler());

    sys->runMetropolis();
    return 0;
}
