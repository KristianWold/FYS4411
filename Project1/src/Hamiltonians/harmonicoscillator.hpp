#pragma once
#include "hamiltonian.hpp"


class HarmonicOscillator : public Hamiltonian
{
public:
    HarmonicOscillator(double omega);
    double localEnergy();

private:
    double m_omega;
};
