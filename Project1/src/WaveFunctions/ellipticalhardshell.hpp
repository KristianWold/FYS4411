#pragma once
#include "wavefunction.hpp"


class EllipticalHardshell : public WaveFunction
{
public:
    EllipticalHardshell(double alpha, double a, double beta);
    double laplacian();
    double evaluate();
    double amplitudeRatio();
    void gradient(double* gradient, int particle, double* position);
    double gradAlpha();
    void initiate();

    double distance(double* pos1, double* pos2);
    double correlation(double* pos1, double* pos2);
    double oneBodyExponent(double* pos1);


private:
    double m_alpha;
    double m_a;
    double m_beta;
    double* m_temp;

    double** m_r12;
};
