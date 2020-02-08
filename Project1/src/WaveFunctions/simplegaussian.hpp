#pragma once
#include "wavefunction.hpp"


class SimpleGaussian : public WaveFunction
{
public:
    SimpleGaussian(double alpha);
    double kineticEnergy();
    double amplitudeRatio();
    double* gradient();

private:
    double m_alpha;
};
