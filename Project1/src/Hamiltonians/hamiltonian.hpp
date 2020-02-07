#pragma once

class Hamiltonian
{
public:
    void setSystem(class System* sys){m_sys = sys;}
    class System* getSystem(){return m_sys;}

    virtual double localEnergy() = 0;


protected:
    class System* m_sys;
};
