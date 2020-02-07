#include "src/system.hpp"
#include "src/particles.hpp"
#include "src/Hamiltonians/hamiltonian.hpp"
#include "src/Hamiltonians/harmonicoscillator.hpp"
#include "src/WaveFunctions/wavefunction.hpp"
#include "src/WaveFunctions/simplegaussian.hpp"
#include <iostream>

int main() {
    double positions[6] = {1,2,6,4,5,6};
    System* sys = new System();
    sys->setNumParticles(2);
    sys->setNumDim(3);
    sys->setParticles(new Particles(positions));
    sys->setWaveFunction(new SimpleGaussian(0.5));
    sys->setHamiltonian(new HarmonicOscillator(1));

    std::cout << sys->getHamiltonian()->localEnergy() << std::endl;


    return 0;
}
