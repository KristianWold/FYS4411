#pragma once
#include "wavefunction.hpp"


class Hardshell : public WaveFunction
{
public:
    Hardshell(double alpha, double a);
    double laplacian();
    double evaluate();
    double amplitudeRatio();
    void gradient(double* gradient, int particle, double* position);
    double gradAlpha();
    void initiate();

    double correlation(double* pos1, double* pos2);
    double oneBodyExponent(double* pos1);

private:
    double m_alpha;
    double m_a;
};
