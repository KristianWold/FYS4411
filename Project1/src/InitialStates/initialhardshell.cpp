#include "initialhardshell.hpp"
#include "initialstate.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "../WaveFunctions/wavefunction.hpp"
#include "../WaveFunctions/hardshell.hpp"
#include <iostream>

void InitialHardshell::normalSpred(double std)
{
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();

    for (int i = 0; i < numPart; i++)
    {
        for (int j = 0; j < numDim; j++)
        {
            particles->position(i, j) = std*m_sys->getRandomNormal();
        }
    }
}

void InitialHardshell::initiate()
{
    InitialState::initiate();
    double std = 1;
    int count = 0;
    int maxCount = 100;
    double corr = 0;
    double temp;
    double* pos1, *pos2;

    while ((corr == 0) and (count < maxCount))
    {
        normalSpred(std);

        corr = 1;
        for (int i = 0; i < m_sys->getNumParticles(); i++)
        {
            pos1 = m_sys->getParticles()->position(i);
            for (int j = i+1; j < m_sys->getNumParticles(); j++)
            {
                pos2 = m_sys->getParticles()->position(j);
                temp = ((Hardshell*) m_sys->getWavefunction())->correlation(pos1, pos2);
                if (temp < corr)
                {
                    corr = temp;
                }
            }
        }
        std::cout << corr << std::endl;
        std *= 2;
        count += 1;
    }

}
