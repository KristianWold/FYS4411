#include "../Hamiltonians/harmonicoscillator.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "simplegaussiannumerical.hpp"
#include <cmath>


double SimpleGaussianNumerical::laplacian()
{
    double lap = 0;
    int numP = m_sys->getNumParticles();
    int numD = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();

    double psi_plus, psi_minus, psi;

    for (int i = 0; i < numP; i++)
    {
        for (int j = 0; j < numD; j++)
        {
            psi = evaluate();
            particles->adjustPos(m_h, i, j);
            psi_plus = evaluate();
            particles->adjustPos(-2*m_h, i, j);
            psi_minus = evaluate();
            particles->adjustPos(m_h, i, j);

            lap += (psi_plus - 2*psi + psi_minus);

        }
    }
    lap = lap/(m_h*m_h);
    return lap;
}
