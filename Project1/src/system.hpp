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
    double getRandomUniform(){return (*distUniform)(*gen);}
    double getRandomNormal(){return (*distNormal)(*gen);}

    void initiate();
    void runMetropolis();
    double greenFunction(double dt);

    double* (System::*step)(int particle);
    double* stepBruteForce(int particle);
    double* stepImportanceSampling(int particle);

    double (System::*acceptanceRatio)();
    double acceptanceRatioBruteForce();
    double acceptanceRatioImportanceSampling();

protected:
    int m_numParticles;
    int m_numDim;
    int m_metropolisSteps;
    double m_stepLength;
    double* m_step;
    double* m_gradientOld;
    double* m_gradientNew;

    InitialState* m_initState;
    Hamiltonian* m_hamiltonian;
    WaveFunction* m_wavefunction;
    Particles* m_particles;
    Sampler* m_sampler;

    std::mt19937* gen;
    std::uniform_real_distribution<double>* distUniform;
    std::normal_distribution<double>* distNormal;
};
