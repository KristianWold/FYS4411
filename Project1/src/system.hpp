#pragma once
#include <random>

class System
{
public:
    //Setters
    void setNumParticles(int numParticles){m_numParticles = numParticles;}
    void setNumDim(int numDim){m_numDim = numDim;}
    void setInitialState(class InitialState* initState);
    void setHamiltonian(class Hamiltonian* hamiltonian);
    void setWaveFunction(class WaveFunction* wavefunction);
    void setParticles(class Particles* particles);
    void setSeed(int seed);

    //Getters
    int getNumParticles(){return m_numParticles;}
    int getNumDim(){return m_numDim;}
    InitialState* getInititalState(){return m_initState;}
    Hamiltonian* getHamiltonian(){return m_hamiltonian;}
    WaveFunction* getWavefunction(){return m_wavefunction;}
    Particles* getParticles(){return m_particles;}
    double getRandomUniform(){return dist(gen);}

    void runMetropolis(int numMetropolisSteps);
    double* step();

protected:
    int m_numParticles;
    int m_numDim;

    InitialState* m_initState;
    Hamiltonian* m_hamiltonian;
    WaveFunction* m_wavefunction;
    Particles* m_particles;

    double m_stepLength = 0.05;

    std::mt19937 gen;
    std::uniform_real_distribution<double> dist;
};
