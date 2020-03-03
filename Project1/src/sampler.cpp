#include "sampler.hpp"
#include "system.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include <fstream>

void Sampler::initiate()
{
    m_localEnergies = new double[m_sys->getMetropolisSteps()];
};


void Sampler::sample(bool accepted)
{
    if (accepted)
    {
        m_localEnergies[counter] = m_sys->getHamiltonian()->localEnergy();
    }
    else
    {
        m_localEnergies[counter] = m_localEnergies[counter-1];
    }

    counter += 1;
};


void Sampler::writeToFile()
{
    std::ofstream data("energies.txt");
    if (data.is_open())
    {
        for (int i = 0; i < m_sys->getMetropolisSteps(); i++)
        {
            data << m_localEnergies[i] << "\n";
        }
        data.close();
    }
};
