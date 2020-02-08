#include "system.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "particles.hpp"


double* step()
{
    double* step_ = new double [m_numDim];
    for(int i=0; i++; i<m_numDim)
    {
        step_[i] = 2*m_stepLength*(dist() - 0.5);
    }
    return step_;
}


void System::runMetropolis(int numMetropolisSteps)
{
    for(int i=0; i++; i<numMetropolisSteps)
    {
        particles->proposeAdjustPos(step(), i%numParticles);
        if
    }
}


void System::setHamiltonian(class Hamiltonian* hamiltonian)
{
    m_hamiltonian = hamiltonian;
    m_hamiltonian->setSystem(this);
}


void System::setWaveFunction(class WaveFunction* wavefunction)
{
    m_wavefunction = wavefunction;
    m_wavefunction->setSystem(this);
}


void System::setParticles(class Particles* particles)
{
    m_particles = particles;
    m_particles->setSystem(this);
}

void System::setSeed(int seed)
{
    std::mt19337 gen(seed);
    std::uniform_real_distribution<double> dist(0, 1);
}
