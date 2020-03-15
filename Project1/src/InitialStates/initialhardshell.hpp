#pragma once
#include "initialstate.hpp"
#include "../particles.hpp"

class InitialHardshell : public InitialState
{
public:
    void initiate();
    void normalSpred(double std);
};
