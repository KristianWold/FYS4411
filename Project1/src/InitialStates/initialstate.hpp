#pragma once
#include<iostream>

class InitialState
{
public:
    void setSystem(class System* sys){m_sys = sys;}
    virtual void initiate();

protected:
    class System* m_sys;
};
