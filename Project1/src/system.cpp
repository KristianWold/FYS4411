#include "system.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "Hamiltonians/hamiltonian.hpp"
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

    for(int i=0; i < numMetropolisSteps; i++)
    {
        //std::cout << step()[0] << std::endl;
        m_particles->proposeAdjustPos(step(), i%m_numParticles);
        //std::cout << m_wavefunction->amplitudeRatio() << "  " << dist(gen) << std::endl;
        if (m_wavefunction->amplitudeRatio() > dist(gen))
        {
            //std::cout << "success  " << i << std::endl;
            m_particles->commitAdjustPos();

        //    std::cout << m_particles->getPosition(1,2) << std::endl;
        }
        std::cout << m_hamiltonian->localEnergy() << std::endl;
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
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(0, 1);
}
