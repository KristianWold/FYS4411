#include "randomuniform.hpp"
#include "initialstate.hpp"
#include "../system.hpp"
#include "../particles.hpp"


void RandomUniform::initiate()
{
    InitialState::initiate();
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();

    for (int i = 0; i < numPart; i++)
    {
        for (int j = 0; j < numDim; j++)
        {
            particles->position(i, j) = 2*(m_sys->getRandomUniform() - 0.5);
        }
    }
}
