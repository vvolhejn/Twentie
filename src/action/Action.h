#pragma once
#include "Types.h"
#include "State.h"
#include "Controller.h"

class Action {
public:
    virtual ~Action(){};
    virtual void execute(const State& s) = 0;
    virtual bool hasEnded(const State& s) = 0;
protected:
    u32 startFrame;
};
