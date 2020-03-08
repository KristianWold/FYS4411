#include "sampler.hpp"
#include "system.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "particles.hpp"
#include <fstream>

void Sampler::initiate()
{
    m_localEnergies = new std::ofstream("localEnergies.txt");
    m_configurations = new std::ofstream("configuration.txt");
}


void Sampler::sample(bool accepted)
{
    if (accepted)
    {
        m_localEnergyOld = m_sys->getHamiltonian()->localEnergy();
    }

    if (m_localEnergies->is_open())
    {
        (*m_localEnergies) << m_localEnergyOld << "\n";
    }

    if (m_configurations->is_open())
    {
        for (int i = 0; i < m_sys->getNumParticles(); i++)
        {
            for (int j = 0; j < m_sys->getNumDim(); j++)
            {
                (*m_configurations) <<
                m_sys->getParticles()->position(i,j)
                                    << "\n";
            }
        }
    }
}


void Sampler::close()
{
    m_localEnergies->close();
    m_configurations->close();
};
