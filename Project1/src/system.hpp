#pragma once

#include <random>

class System
{
public:
    void setNumParticles(int numParticles){m_numParticles = numParticles;}
    void setNumDim(int numDim){m_numDim = numDim;}
    void setHamiltonian(class Hamiltonian* hamiltonian);
    void setWaveFunction(class WaveFunction* wavefunction);
    void setParticles(class Particles* particles);

    int getNumParticles(){return m_numParticles;}
    int getNumDim(){return m_numDim;}
    class Hamiltonian* getHamiltonian(){return m_hamiltonian;}
    class WaveFunction* getWavefunction(){return m_wavefunction;}
    class Particles* getParticles(){return m_particles;}

    void runMetropolis(int numMetropolisSteps);
    double* step();

protected:
    int m_numParticles;
    int m_numDim;
    class Hamiltonian* m_hamiltonian;
    class WaveFunction* m_wavefunction;
    class Particles* m_particles;

    int m_seed;
};
