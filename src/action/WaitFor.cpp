#include "WaitFor.h"
#include <iostream>

WaitFor::WaitFor(std::function<bool(const State&)> _cond) {
    condition = _cond;
}

WaitFor::WaitFor(u32 _endFrame) {
    endFrame = _endFrame;
}

WaitFor::~WaitFor(){
}

void WaitFor::execute(const State &s) {}

bool WaitFor::hasEnded(const State& s) {
    if(endFrame != 0 && s.frame >= endFrame) return true;
    return condition(s);
}
/*
bool WaitFor::canWaitFor(const State& s) {
    if(s.me.airSpeedY + s.me.airSpeedY > 0) return true; //flying up
    if(s.me.y > 30) return true; //too high
    if(s.me.y > 0 && (-s.distanceToEdge(ME) / s.me.y) < 0.15) return true; //close to the stage
    return false;
}*/
