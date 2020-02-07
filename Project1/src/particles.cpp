#include "particles.hpp"

Particles::Particles(double* positions)
{
    m_positions = positions;
}

double Particles::getPosition(int particle, int dim)
{
    return m_positions[dim*particle + dim];
}
