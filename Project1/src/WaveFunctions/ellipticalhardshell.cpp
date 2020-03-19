#include "../Hamiltonians/harmonicoscillator.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "ellipticalhardshell.hpp"
#include <cmath>
#include <iostream>

EllipticalHardshell::EllipticalHardshell(double alpha, double a, double beta)
{
    m_alpha = alpha;
    m_a = a;
    m_beta = beta;
}

double EllipticalHardshell::distance(double* pos1, double* pos2)
{
    double r12 = 0;
    double temp;
    for(int i = 0; i < m_sys->getNumDim(); i++)
    {
        temp = (pos1[i] - pos2[i]);
        r12 += temp*temp;
    }
    r12 = std::sqrt(r12);
    return r12;
}

double EllipticalHardshell::correlation(double* pos1, double* pos2)
{
    double temp;
    double r12 = distance(pos1, pos2);
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

double EllipticalHardshell::oneBodyExponent(double* pos)
{
    double expo = 0;
    expo += pos[0]*pos[0];
    expo += pos[1]*pos[1];
    expo += m_beta*pos[2]*pos[2];
    return expo;
}

double EllipticalHardshell::evaluate()
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

double EllipticalHardshell::amplitudeRatio()
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

double EllipticalHardshell::laplacian()
{
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();

    double *pos1, *pos2;
    double grad[3], temp[3];
    double r12, temp1, temp2, temp3, temp4, lap = 0;

    for (int i = 0; i < numPart; i++)
    {
        temp1 = temp2 = temp3 = temp4 = 0;
        pos1 = particles->position(i);
        gradient(grad, i, pos1);
        for (int k = 0; k < numDim; k++)
        {
            temp[k] = 0;
        }

        for (int j = 0; j < numPart; j++)
        {
            if (i != j)
            {
                pos2 = particles->position(j);
                r12 = distance(pos1, pos2);

                temp2 += (m_a - 2*r12)*m_a/(r12*r12*(r12 - m_a)*(r12 - m_a));
                temp2 += 2*m_a/(r12*r12*(r12 - m_a));

                for (size_t k = 0; k < numDim; k++)
                {
                    temp[k] += (pos1[k] - pos2[k])*m_a/(r12*r12*(r12 - m_a));
                }
            }
        }

        for (size_t k = 0; k < numDim; k++)
        {
            temp3 += grad[k]*temp[k];
            temp4 += temp[k]*temp[k];
        }
        temp3 *= 2;

        lap += m_alpha*(4*m_alpha*oneBodyExponent(pos1) - 2*numDim) + temp2 + temp3 + temp4;
    }
    return lap;
}


double EllipticalHardshell::gradAlpha()
{
    double temp = 0;
    double pos = 0;
    Particles* particles = m_sys->getParticles();
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();

    for(int i = 0; i < numPart; i++)
    {
        temp += oneBodyExponent(particles->position(i));

    }
    return -temp;
}


void EllipticalHardshell::gradient(double* gradient, int particle, double* position)
{

    double pos1, pos2, temp, r12 = 0;
    Particles* particles = m_sys->getParticles();
    int numPart = m_sys->getNumParticles();
    int numDim = m_sys->getNumDim();
    for (int j = 0; j < numDim; j++)
    {
        m_temp[j] = 0;
    }

    for (int i = 0; i < numPart; i++)
    {
        if (i != particle)
        {
            r12 = distance(position, particles->position(i));
            temp = m_a/(r12*r12*(r12 - m_a));

            for (int j = 0; j < numDim; j++)
            {
                m_temp[j] += (position[j] - particles->position(i,j))*temp;
            }
        }
    }

    gradient[0] = (m_temp[0] - 2*m_alpha)*position[0];
    gradient[1] = (m_temp[1] - 2*m_alpha)*position[1];
    gradient[2] = (m_temp[0] - 2*m_alpha*m_beta)*position[2];
}


void EllipticalHardshell::initiate()
{
    m_temp = new double[m_sys->getNumDim()];

    m_r12 = new double*[m_sys->getNumParticles()];
    for (int i = 0; i < m_sys->getNumParticles(); i++)
    {
        m_r12[i] = new double[m_sys->getNumParticles()];
    }
};
