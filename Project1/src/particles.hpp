#pragma once

class Particles
{
public:
    void setSystem(class System* sys);
    System* getSystem(){return m_sys;}

    double& position(int particle, int dim);
    double* position(int particle);
    double* getAdjustPos();
    int getMovedParticle();
    void adjustPos(double step, int movedParticle, int dim);
    void proposeAdjustPos(double* step, int movedParticle);
    void commitAdjustPos();

protected:
    double** m_positions;
    double* m_adjustedPos;
    System* m_sys;
    int m_movedParticle;
};
