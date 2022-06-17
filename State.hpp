#pragma once
#ifndef STATE_H
#define STATE_H

template<class T>
class State
{
public:
    virtual void Enter(T *)=0;
    virtual void Update(T *)=0;
    virtual void Execute(T *)=0;
    virtual void Exit(T *)=0;
};

#endif