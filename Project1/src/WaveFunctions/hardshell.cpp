#include "../Hamiltonians/harmonicoscillator.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "hardshell.hpp"
#include <cmath>
#include <iostream>

Hardshell::Hardshell(double alpha, double a)
{
    m_alpha = alpha;
    m_a = a;
}

double Hardshell::correlation(double* pos1, double* pos2)
{
    double r12 = 0;
    double temp;
    for(int i = 0; i < m_sys->getNumDim(); i++)
    {
        temp = (pos1[i] - pos2[i]);
        r12 += temp*temp;
    }
    r12 = std::sqrt(r12);

    if (r12 > m_a)
    {
        temp = 1 - m_a/r12;
    }
    else
    {
        temp = 0;
    }

    return temp;
}

double Hardshell::oneBodyExponent(double* pos)
{
    double expo = 0;
    for(int i = 0; i < m_sys->getNumDim(); i++)
    {
        expo += pos[i]*pos[i];
    }
    return expo;
}

double Hardshell::evaluate()
{
    double expo = 0;
    double corr = 1;
    Particles* particles = m_sys->getParticles();
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();

    for(int i = 0; i < numPart; i++)
    {
        expo += oneBodyExponent(particles->position(i));

        for(int j = i+1; j < numPart; j++)
        {
            corr *= correlation(particles->position(i), particles->position(j));
        }
    }
    return std::exp(-m_alpha*expo)*corr;
}

double Hardshell::amplitudeRatio()
{
    double expo = 0;
    double corr = 1;
    Particles* particles = m_sys->getParticles();

    int movedParticle = particles->getMovedParticle();
    double* adjustPos = particles->getAdjustPos();

    expo += oneBodyExponent(particles->getAdjustPos());
    expo -= oneBodyExponent(particles->position(movedParticle));

    for(int i = 0; i < movedParticle; i++)
    {
        corr *= correlation(adjustPos, particles->position(i));
        corr /= correlation(particles->position(movedParticle), particles->position(i));
    }
    for(int i = movedParticle + 1; i < m_sys->getNumParticles(); i++)
    {
        corr *= correlation(adjustPos, particles->position(i));
        corr /= correlation(particles->position(movedParticle), particles->position(i));
    }

    return std::exp(-2*m_alpha*expo)*corr*corr;
}

double Hardshell::laplacian()
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


double Hardshell::gradAlpha()
{
    double temp = 0;
    double pos = 0;
    Particles* particles = m_sys->getParticles();
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();

    for(int i = 0; i < numPart; i++)
    {
        for (int j = 0; j < numDim; j++)
        {
            pos = particles->position(i, j);
            temp += pos*pos;
        }

    }
    return -temp;
}


void Hardshell::initiate(){};


void Hardshell::gradient(double* gradient, int particle, double* position)
{
    for (int i = 0; i < m_sys->getNumDim(); i++)
    {
        gradient[i] = -2*m_alpha*position[i];
    }
}
