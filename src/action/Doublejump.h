#pragma once
#include "action/Action.h"
#include "State.h"

class Doublejump: public Action {
public:
    Doublejump(u32 frame, float _di);
    ~Doublejump();
    void execute(const State &s);
    bool hasEnded(const State& s);
private:
    float di;
};
