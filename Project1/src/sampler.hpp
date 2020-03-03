#pragma once

class Sampler
{
public:
    void setSystem(class System* sys){m_sys = sys;}
    void initiate();
    void sample(bool accepted);
    void writeToFile();

private:
    class System* m_sys;
    double* m_localEnergies;
    int counter = 0;
};
