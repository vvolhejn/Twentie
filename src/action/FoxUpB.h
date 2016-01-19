#pragma once
#include "action/Action.h"
#include "State.h"

class FoxUpB: public Action {
public:
    FoxUpB(u32 frame);
    ~FoxUpB();
    void execute(const State &s);
    bool hasEnded(const State& s);
private:
    inline void aimTo(const State& s, float x, float y);
    float di;
};

