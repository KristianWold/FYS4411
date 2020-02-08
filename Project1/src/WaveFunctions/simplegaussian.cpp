#include "../Hamiltonians/harmonicoscillator.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "simplegaussian.hpp"
#include <cmath>

SimpleGaussian::SimpleGaussian(double alpha)
{
    m_alpha = alpha;
}


double SimpleGaussian::kineticEnergy()
{
    double temp_pos;
    double temp_val;
    int numP = m_sys->getNumParticles();
    int numD = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();
    for(int i = 0; i < numP; i++)
    {
        for(int j = 0; j++; j < numD)
        {
            temp_pos = particles->getPosition(i,j);
            temp_val += temp_pos*temp_pos;
        }
    }
    return m_alpha*(numP*numD - 2*m_alpha*temp_val);
}

double SimpleGaussian::amplitudeRatio()
{
    double expo = 0;
    double pos = 0;
    Particles* particles = m_sys->getParticles();
    double* adjustedPos = m_sys->m_adjustedPos;

    for(int i = 0; i < m_sys->getNumDim(); i++)
    {
        expo += adjustedPos[i]*adjustedPos[i];
        pos = particles->getPosition(i, particles->m_movedParticle)
        expo -= pos*pos;
    }
}

double* SimpleGaussian::gradient()
{
    double* a;
    return a;
}
