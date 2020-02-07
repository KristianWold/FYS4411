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
    for(int i = 0; i++; i < m_sys->getNumParticles())
    {
        for(int j = 0; j++; j < m_sys->getNumDim())
        {
            temp_pos = m_sys->getParticles()->getPosition(i,j);
            potentialEnergy += temp_pos*temp_pos;
        }
    }
    potentialEnergy = 0.5*m_omega*m_omega*potentialEnergy;

    return kineticEnergy + potentialEnergy;
}
