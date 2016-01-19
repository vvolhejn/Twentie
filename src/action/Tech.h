#pragma once
#include "action/Action.h"
#include "State.h"

class Tech: public Action {
public:
    Tech(u32 frame);
    ~Tech();
    void execute(const State &s);
    bool hasEnded(const State& s);
};
