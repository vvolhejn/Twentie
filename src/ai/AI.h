#pragma once
#include "Types.h"
#include "State.h"

class AI {
public:
    virtual ~AI(){};
    //It is possibly more clean to have the AI return a vector of actions to be performed?
    virtual void decide(const State& s) = 0;
};
