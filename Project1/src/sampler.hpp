#pragma once
#include <fstream>

class Sampler
{
public:
    void setSystem(class System* sys){m_sys = sys;}
    void initiate();
    void sample(bool accepted);
    void close();

private:
    class System* m_sys;
    double  m_localEnergy, m_localEnergyOld;
    double m_gradientAlpha, m_gradientAlphaOld;
    double m_LEGA, m_LEGAOld;
    std::ofstream* m_localEnergies;
    std::ofstream* m_configurations;
    std::ofstream* m_metadata;
};
