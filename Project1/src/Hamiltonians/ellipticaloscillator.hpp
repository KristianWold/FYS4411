#pragma once
#include "hamiltonian.hpp"


class EllipticalOscillator : public Hamiltonian
{
public:
    EllipticalOscillator(double omega);
    double localEnergy();

private:
    double m_omega;
};
