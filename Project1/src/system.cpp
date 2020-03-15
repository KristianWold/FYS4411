#include "system.hpp"
#include "InitialStates/initialstate.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "particles.hpp"
#include "sampler.hpp"

#include <string>
#include <random>
#include <iostream>
#include <cmath>

double* System::stepBruteForce(int particle)
{
    for(int i = 0; i < getNumDim(); i++)
    {
        m_step[i] = 2*m_stepLength*(getRandomUniform() - 0.5);
    }
    return m_step;
}


double* System::stepImportanceSampling(int particle)
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

double System::acceptanceRatioBruteForce()
{
    return getWavefunction()->amplitudeRatio();
}

double System::acceptanceRatioImportanceSampling()
{
    return greenFunction(m_stepLength)*getWavefunction()->amplitudeRatio();
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
    int particle;
    initiate();
    getSampler()->sample(true);

    step = &System::stepImportanceSampling;
    acceptanceRatio = &System::acceptanceRatioImportanceSampling;
    m_acceptanceRate = 0;

    for(int i=0; i < m_metropolisSteps - 1; i++)
    {
        particle = i%m_numParticles;
        getParticles()->proposeAdjustPos((this->*step)(particle), particle);

        accepted = ((this->*acceptanceRatio)() > getRandomUniform());
        if (accepted)
        {
            getParticles()->commitAdjustPos();
            m_acceptanceRate += 1;
        }

        getSampler()->sample(accepted);
    }
    m_acceptanceRate /= getMetropolisSteps();

    getSampler()->close();
}

void System::setName(std::string name)
{
    m_name = name;
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
