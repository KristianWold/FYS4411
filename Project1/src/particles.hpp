#pragma once

class Particles
{
public:
    void setSystem(class System* sys);
    class System* getSystem(){return m_sys;}

    double getPosition(int particle, int dim);
    void proposeAdjustPos(double* step, int whichParticle);
    void commitAdjustPos();

protected:
    double* m_positions;
    double* adjustedPos;
    class System* m_sys;
    int m_movedParticle;
};
