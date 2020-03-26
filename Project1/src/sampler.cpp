#include "sampler.hpp"
#include "system.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "particles.hpp"

#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>
#include <iomanip>



void Sampler::initiate()
{
    m_localEnergies = new std::ofstream(
        m_sys->m_directory + "/localEnergies_" +
        m_sys->m_thread + ".txt"
    );
    m_configurations = new std::ofstream(
        m_sys->m_directory + "/configuration_"+
        m_sys->m_thread + ".txt"
    );
    m_gradient = new std::ofstream(
        m_sys->m_directory + "/gradient_" +
        m_sys->m_thread + ".txt"
    );
    m_metadata = new std::ofstream(
        m_sys->m_directory + "/metadata_" +
        m_sys->m_thread + ".txt"
    );
    assert (m_metadata->is_open());
}


void Sampler::sample(bool accepted)
{
    if (accepted)
    {
        m_localEnergyOld = m_sys->getHamiltonian()->localEnergy();
        m_gradientAlphaOld = m_sys->getWavefunction()->gradAlpha();
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
                std::setprecision(3) <<
                m_sys->getParticles()->position(i,j)
                                    << "\n";
            }
        }
    }

    if (m_gradient->is_open())
    {
        (*m_gradient) << m_gradientAlphaOld << "\n";
    }
}


void Sampler::close()
{
    if (m_metadata->is_open())
    {
        (*m_metadata) << m_sys->m_acceptanceRate << "\n";
    }

    m_localEnergies->close();
    m_configurations->close();
    m_gradient->close();
    m_metadata->close();

};
