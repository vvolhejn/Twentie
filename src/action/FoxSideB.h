#pragma once
#include "action/Action.h"
#include "State.h"

class FoxSideB: public Action {
public:
    FoxSideB(u32 frame, bool right);
    ~FoxSideB();
    void execute(const State &s);
    bool hasEnded(const State& s);
private:
    bool right;
};
