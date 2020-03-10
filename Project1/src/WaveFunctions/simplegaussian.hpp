#pragma once
#include "wavefunction.hpp"


class SimpleGaussian : public WaveFunction
{
public:
    SimpleGaussian(double alpha);
    double laplacian();
    double evaluate();
    double amplitudeRatio();
    void gradient(double* gradient, int particle, double* position);
    double gradAlpha();
    void initiate();

private:
    double m_alpha;
};
