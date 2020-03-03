#include "system.hpp"
#include "InitialStates/initialstate.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "particles.hpp"
#include "sampler.hpp"

#include <random>
#include <iostream>


double* System::step()
{
    double* step_ = new double [getNumDim()];
    for(int i = 0; i < getNumDim(); i++)
    {
        step_[i] = 2*m_stepLength*(getRandomUniform() - 0.5);
    }
    return step_;
}

void System::initiate()
{
    m_initState->initiate();
    m_sampler->initiate();
}

void System::runMetropolis()
{
    bool accepted;
    int total = 0;
    initiate();
    getSampler()->sample(true);

    for(int i=0; i < m_metropolisSteps - 1; i++)
    {
        getParticles()->proposeAdjustPos(step(), i%m_numParticles);
        accepted = (getWavefunction()->amplitudeRatio() > getRandomUniform());

        if (accepted)
        {
            getParticles()->commitAdjustPos();
            total += 1;
        }
        getSampler()->sample(accepted);
    }
    getSampler()->writeToFile();
    std::cout << total << "/" << m_metropolisSteps << std::endl;
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

void System::setSampler(Sampler* sampler)
{
    m_sampler = sampler;
    m_sampler->setSystem(this);
}

void System::setSeed(int seed)
{
    gen = new std::mt19937(seed);
    dist = new std::uniform_real_distribution<double>(0, 1);
}
