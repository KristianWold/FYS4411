#include "../WaveFunctions/wavefunction.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "ellipticaloscillator.hpp"


EllipticalOscillator::EllipticalOscillator(double omega)
{
    m_omega = omega;
}

double EllipticalOscillator::localEnergy()
{
    double temp_pos;
    double kineticEnergy = -0.5*(m_sys->getWavefunction()->laplacian());
    double potentialEnergy = 0;
    int numP = m_sys->getNumParticles();
    Particles* particles = m_sys->getParticles();

    for(int i = 0; i < numP; i++)
    {
        temp_pos = particles->position(i,0);
        potentialEnergy += temp_pos*temp_pos;

        temp_pos = particles->position(i,1);
        potentialEnergy += temp_pos*temp_pos;

        temp_pos = particles->position(i,2);
        potentialEnergy += m_omega*m_omega*temp_pos*temp_pos;
    }
    potentialEnergy = 0.5*potentialEnergy;

    return kineticEnergy + potentialEnergy;
}
