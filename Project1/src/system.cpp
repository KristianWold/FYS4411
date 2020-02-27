#include "system.hpp"
#include "InitialStates/initialstate.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "particles.hpp"

#include <random>
#include <iostream>


double* System::step()
{
    double* step_ = new double [m_numDim];
    for(int i = 0; i < m_numDim; i++)
    {
        step_[i] = 2*m_stepLength*(dist(gen) - 0.5);
    }
    return step_;
}


void System::runMetropolis(int numMetropolisSteps)
{
    double amp;
    int total = 0;

    m_initState->setupInitialSystem();

    for(int i=0; i < numMetropolisSteps; i++)
    {
        amp = m_wavefunction->amplitudeRatio();
        m_particles->proposeAdjustPos(step(), i%m_numParticles);
        if (amp > dist(gen))
        {
            total+=1;
            m_particles->commitAdjustPos();
        }
    }
    std::cout << total <<"/" << numMetropolisSteps << std::endl;
}

void System::setInitialState(InitialState* initState)
{
    m_initState = initState;
    m_initState->setSystem(this);
}

void System::setHamiltonian(Hamiltonian* hamiltonian)
{
    m_hamiltonian = hamiltonian;
    m_hamiltonian->setSystem(this);
}


void System::setWaveFunction(WaveFunction* wavefunction)
{
    m_wavefunction = wavefunction;
    m_wavefunction->setSystem(this);
}


void System::setParticles(Particles* particles)
{
    m_particles = particles;
    m_particles->setSystem(this);
}

void System::setSeed(int seed)
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(0, 1);
}
