#pragma once
#include <random>

class System
{
public:
    //Setters
    void setNumParticles(int numParticles){m_numParticles = numParticles;}
    void setNumDim(int numDim){m_numDim = numDim;}
    void setStepLength(double steplength){m_stepLength = steplength;}
    void setMetropolisSteps(int metropolisSteps){m_metropolisSteps = metropolisSteps;}

    void setInitialState(class InitialState* initState);
    void setHamiltonian(class Hamiltonian* hamiltonian);
    void setWaveFunction(class WaveFunction* wavefunction);
    void setParticles(class Particles* particles);
    void setSampler(class Sampler* sampler);

    void setSeed(int seed);

    //Getters
    int getNumParticles(){return m_numParticles;}
    int getNumDim(){return m_numDim;}
    int getMetropolisSteps(){return m_metropolisSteps;}
    InitialState* getInititalState(){return m_initState;}
    Hamiltonian* getHamiltonian(){return m_hamiltonian;}
    WaveFunction* getWavefunction(){return m_wavefunction;}
    Particles* getParticles(){return m_particles;}
    Sampler* getSampler(){return m_sampler;}
    double getRandomUniform(){return (*dist)(*gen);}

    void initiate();
    void runMetropolis();
    double* step();

protected:
    int m_numParticles;
    int m_numDim;
    int m_metropolisSteps;
    double m_stepLength;

    InitialState* m_initState;
    Hamiltonian* m_hamiltonian;
    WaveFunction* m_wavefunction;
    Particles* m_particles;
    Sampler* m_sampler;

    std::mt19937* gen;
    std::uniform_real_distribution<double>* dist;
};
