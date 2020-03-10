#pragma once

class WaveFunction
{
public:
    void setSystem(class System* sys){m_sys = sys;}
    class System* getSystem(){return m_sys;}

    virtual double evaluate() = 0;
    virtual double amplitudeRatio() = 0;
    virtual void gradient(double* gradient, int particle, double* position) = 0;
    virtual double laplacian() = 0;
    virtual double gradAlpha() = 0;
    virtual void initiate(){};

protected:
    class System* m_sys;
};
