#include "system.hpp"
#include "InitialStates/initialstate.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "particles.hpp"
#include "sampler.hpp"

#include <random>
#include <iostream>
#include <cmath>

double* System::step(int particle)
{
    for(int i = 0; i < getNumDim(); i++)
    {
        m_step[i] = 2*m_stepLength*(getRandomUniform() - 0.5);
    }
    return m_step;
}


double* System::step2(int particle)
{
    Particles* particles = getParticles();
    double* position = particles->position(particle);

    double sqrtdt = std::sqrt(m_stepLength);
    getWavefunction()->gradient(m_gradientOld, particle, position);
    for(int i = 0; i < getNumDim(); i++)
    {
        m_step[i] = m_gradientOld[i]*m_stepLength + getRandomNormal()*sqrtdt;
    }
    return m_step;
}


double System::greenFunction(double dt)
{
    int numDim = getNumDim();
    Particles* particles = getParticles();
    int movedParticle = particles->getMovedParticle();

    double* x = particles->position(movedParticle);
    double* y = particles->getAdjustPos();

    getWavefunction()->gradient(m_gradientNew, movedParticle, y);

    double temp1, temp2, expo = 0;
    for (int i = 0; i < numDim; i++)
    {
        temp1 = (x[i] - y[i] - m_gradientNew[i]*dt);
        temp1 = temp1*temp1;

        temp2 = (y[i] - x[i] - m_gradientOld[i]*dt);
        temp2 = temp2*temp2;

        expo -=  (temp1 - temp2);
    }
    expo /= 2*dt;
    return std::exp(expo);
}


void System::initiate()
{
    m_initState->initiate();
    m_wavefunction->initiate();
    m_sampler->initiate();

    m_step = new double [getNumDim()];
    m_gradientOld = new double [getNumDim()];
    m_gradientNew = new double [getNumDim()];
}


void System::runMetropolis()
{
    bool accepted;
    int particle, total = 0;
    initiate();
    getSampler()->sample(true);

    for(int i=0; i < m_metropolisSteps - 1; i++)
    {
        particle = i%m_numParticles;
        getParticles()->proposeAdjustPos(step(particle), particle);

        accepted = (getWavefunction()->amplitudeRatio() > getRandomUniform());

        if (accepted)
        {
            getParticles()->commitAdjustPos();
            total += 1;
        }

        getSampler()->sample(accepted);
    }
    
    std::cout << total << "/" << m_metropolisSteps << std::endl;
    getSampler()->close();
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
    distUniform = new std::uniform_real_distribution<double>(0, 1);
    distNormal = new std::normal_distribution<double>(0, 1);
}
