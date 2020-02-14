#pragma once

class Particles
{
public:
    void setSystem(class System* sys);
    class System* getSystem(){return m_sys;}

    double getPosition(int particle, int dim);
    double* getAdjustPos();
    int getMovedParticle();
    void proposeAdjustPos(double* step, int movedParticle);
    void commitAdjustPos();

protected:
    double* m_positions;
    double* m_adjustedPos;
    class System* m_sys;
    int m_movedParticle;
};
