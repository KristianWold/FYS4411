#include "system.hpp"
#include "WaveFunctions/wavefunction.hpp"
#include "Hamiltonians/hamiltonian.hpp"
#include "particles.hpp"

void System::setHamiltonian(class Hamiltonian* hamiltonian)
{
    m_hamiltonian = hamiltonian;
    m_hamiltonian->setSystem(this);
}

void System::setWaveFunction(class WaveFunction* wavefunction)
{
    m_wavefunction = wavefunction;
    m_wavefunction->setSystem(this);
}
void System::setParticles(class Particles* particles)
{
    m_particles = particles;
    m_particles->setSystem(this);
}
