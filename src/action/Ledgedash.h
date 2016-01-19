#pragma once
#include "action/Action.h"
#include "State.h"

//Fox only, though. Still very inconsistent, but will SD only rarely.
class Ledgedash: public Action {
public:
    Ledgedash(u32 frame);
    ~Ledgedash();
    void execute(const State &s);
    bool hasEnded(const State& s);
};
