#pragma once


class InitialState
{
public:
    void setSystem(class System* sys){m_sys = sys;}
    virtual void setupInitialSystem();

protected:
    class System* m_sys;
};
