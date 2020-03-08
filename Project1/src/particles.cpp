#include "particles.hpp"
#include "system.hpp"
#include <iostream>

void Particles::setSystem(System* sys)
{
    m_sys = sys;
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();

    m_positions = new double* [numPart];
    for (int i = 0; i < numPart; i++)
    {
        m_positions[i] = new double [numDim];
        for(int j=0; j < numDim; j++)
        {
            m_positions[i][j] = 0;
        }
    }

    m_adjustedPos = new double [m_sys->getNumDim()];
}

double& Particles::position(int particle, int dim)
{
    return m_positions[particle][dim];
}

double* Particles::position(int particle)
{
    return m_positions[particle];
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
