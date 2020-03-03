#include "particles.hpp"
#include "system.hpp"
#include <iostream>

void Particles::setSystem(System* sys)
{
    m_sys = sys;
    m_positions = new double [m_sys->getNumParticles() * m_sys->getNumDim()];
    for(int i=0; i<m_sys->getNumParticles() * m_sys->getNumDim(); i++)
    {
        m_positions[i] = 0;
    }
    m_adjustedPos = new double [m_sys->getNumDim()];
}

double& Particles::position(int particle, int dim)
{
    return m_positions[m_sys->getNumDim()*particle + dim];
}

void Particles::adjustPos(double step, int movedParticle, int dim)
{
    position(movedParticle, dim) += step;
}

void Particles::proposeAdjustPos(double* step, int movedParticle)
{
    m_movedParticle = movedParticle;
    int numD = m_sys->getNumDim();
    for (int i = 0; i < numD; i++)
    {
        m_adjustedPos[i] = position(m_movedParticle, i) + step[i];
    }
}

void Particles::commitAdjustPos()
{
    for(int i = 0; i < m_sys->getNumDim(); i++)
    {
        position(m_movedParticle, i) = m_adjustedPos[i];
    }
}

double* Particles::getAdjustPos()
{
    return m_adjustedPos;
}

int Particles::getMovedParticle()
{
    return m_movedParticle;
}
