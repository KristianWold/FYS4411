#include "../WaveFunctions/wavefunction.hpp"
#include "../system.hpp"
#include "../particles.hpp"
#include "harmonicoscillator.hpp"


HarmonicOscillator::HarmonicOscillator(double omega)
{
    m_omega = omega;
}

double HarmonicOscillator::localEnergy()
{
    double temp_pos;
    double kineticEnergy = m_sys->getWavefunction()->kineticEnergy();
    double potentialEnergy = 0;
    int numP = m_sys->getNumParticles();
    int numD = m_sys->getNumDim();
    Particles* particles = m_sys->getParticles();

    for(int i = 0; i < numP; i++)
    {
        for(int j = 0; j < numD; j++)
        {
            temp_pos = particles->getPosition(i,j);
            potentialEnergy += temp_pos*temp_pos;
        }
    }
    potentialEnergy = 0.5*m_omega*m_omega*potentialEnergy;

    return kineticEnergy + potentialEnergy;
}
