#include "initialstate.hpp"
#include "../particles.hpp"
#include "../system.hpp"

void InitialState::setupInitialSystem()
{
    m_sys->setParticles(new Particles());
}
