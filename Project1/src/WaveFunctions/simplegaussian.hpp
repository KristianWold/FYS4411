#pragma once
#include "wavefunction.hpp"


class SimpleGaussian : public WaveFunction
{
public:
    SimpleGaussian(double alpha);
    double laplacian();
    double evaluate();
    double amplitudeRatio();
    double* gradient();

private:
    double m_alpha;
};
