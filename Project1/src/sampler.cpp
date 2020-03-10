#include "sampler.hpp"
#include "system.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "particles.hpp"
#include <fstream>

void Sampler::initiate()
{
    m_localEnergies = new std::ofstream("localEnergies.txt");
    m_configurations = new std::ofstream("configuration.txt");
    m_metadata = new std::ofstream("metadata.txt");

    m_localEnergy = 0;
    m_gradientAlpha = 0;
    m_LEGA = 0;
}


void Sampler::sample(bool accepted)
{
    if (accepted)
    {
        m_localEnergyOld = m_sys->getHamiltonian()->localEnergy();
        m_gradientAlphaOld = m_sys->getWavefunction()->gradAlpha();
        m_LEGAOld = m_localEnergyOld*m_gradientAlphaOld;
    }

    m_localEnergy += m_localEnergyOld;
    m_gradientAlpha += m_gradientAlphaOld;
    m_LEGA += m_LEGAOld;

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
    m_localEnergy /= m_sys->getMetropolisSteps();
    m_gradientAlpha /= m_sys->getMetropolisSteps();
    m_LEGA /= m_sys->getMetropolisSteps();

    if (m_metadata->is_open())
    {
        (*m_metadata) << 2*(m_LEGA - m_localEnergy*m_gradientAlpha);
    }

    m_localEnergies->close();
    m_configurations->close();
    m_metadata->close();
};
