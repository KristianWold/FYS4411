#pragma once
#include "simplegaussian.hpp"


class SimpleGaussianNumerical : public SimpleGaussian
{
public:
    SimpleGaussianNumerical(double alpha, double h):SimpleGaussian(alpha)
    {
        m_h = h;
    };
    double laplacian();

private:
    double m_h;
};
