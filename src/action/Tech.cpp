#include "Tech.h"

Tech::Tech(u32 frame) {
    startFrame = frame;
}
Tech::~Tech() {}


void Tech::execute(const State &s) {
    if(s.frame == startFrame) {
        setAnalogButton("L", 1.0);
        setStick(true, 0.5 * (rand() % 3), 0.5);
    }
}

bool Tech::hasEnded(const State& s) {
    return (!s.me.inAir) || s.isOffstage(ME) || (s.frame - startFrame > 5);
}
