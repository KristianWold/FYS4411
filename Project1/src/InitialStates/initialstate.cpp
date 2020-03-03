#include "initialstate.hpp"
#include "../particles.hpp"
#include "../system.hpp"
#include <iostream>

void InitialState::initiate()
{
    m_sys->setParticles(new Particles());
}
