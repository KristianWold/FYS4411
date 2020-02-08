#include "particles.hpp"

void Particles::setSystem(class System sys)
{
    m_sys = sys;
    positions = new double [m_sys->getNumParticles() * m_sys->getNumDim()];
    adjustedPos = new double [m_sys->getNumDim()];
}

double Particles::getPosition(int particle, int dim)
{
    return m_positions[dim*particle + dim];
}

void proposeAdjustPos(double* step, int movedParticle)
{
    m_movedParticle = movedParticle;
    int numP = m_sys->getNumParticles();
    int numD = m_sys->getNumDim();
    for (int i = 0; i < numD; i++)
    {
        adjustedPos[i] = positions[numP*movedParticle + i] + step[i];
    }
}

void commitAdjustPos()
{
    int numP = m_sys->getNumParticles();
    int numD = m_sys->getNumDim();
    for(int i = 0; i++; i < numD)
    {
        positions[numP*whichParticle + i] = adjustedPos[i];
    }
}
