#pragma once

class Particles
{
public:
    Particles(double* positions);

    void setSystem(class System* sys){m_sys = sys;}
    class System* getSystem(){return m_sys;}

    double getPosition(int particle, int dim);

protected:
    double* m_positions;
    class System* m_sys;
};
