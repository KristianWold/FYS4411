#include "../Hamiltonians/harmonicoscillator.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "simplegaussian.hpp"
#include <cmath>
#include <iostream>

SimpleGaussian::SimpleGaussian(double alpha)
{
    m_alpha = alpha;
}

double SimpleGaussian::evaluate()
{
    double expo = 0;
    double pos = 0;
    Particles* particles = m_sys->getParticles();
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();

    for(int i = 0; i < numPart; i++)
    {
        for (int j = 0; j < numDim; j++)
        {
            pos = particles->position(i, j);
            expo += pos*pos;
        }

    }
    return std::exp(-m_alpha*expo);
}

double SimpleGaussian::laplacian()
{
    double temp_pos;
    double temp_val = 0;
    int numP = m_sys->getNumParticles();
    int numD = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();
    for(int i = 0; i < numP; i++)
    {
        for(int j = 0; j < numD; j++)
        {
            temp_pos = particles->position(i, j);
            temp_val += temp_pos*temp_pos;
        }
    }
    return m_alpha*(4*m_alpha*temp_val - 2*numP*numD);
}


void SimpleGaussian::initiate(){};


double SimpleGaussian::amplitudeRatio()
{
    double expo = 0;
    double pos = 0;
    Particles* particles = m_sys->getParticles();
    double* adjustedPos = particles->getAdjustPos();

    for(int i = 0; i < m_sys->getNumDim(); i++)
    {
        expo += adjustedPos[i]*adjustedPos[i];
        pos = particles->position(particles->getMovedParticle(), i);
        expo -= pos*pos;
    }
    return std::exp(-2*m_alpha*expo);
}


void SimpleGaussian::gradient(double* gradient, int particle, double* position)
{
    for (int i = 0; i < m_sys->getNumDim(); i++)
    {
        gradient[i] = -2*m_alpha*position[i];
    }
}
