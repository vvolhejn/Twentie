#include "Ledgedash.h"
#include <iostream>
#include <sys/time.h>

Ledgedash::Ledgedash(u32 frame) {
    startFrame = frame;
}
Ledgedash::~Ledgedash() {}

void Ledgedash::execute(const State &s) {
    bool right = s.me.facingRight;
    //std::cout << (s.frame - startFrame) << ": " << s.me.actionState << " - " << s.me.actionStateFrame << std::endl;
    switch(s.frame - startFrame) {
    case 0:
        setStick(true, right ? 0 : 1, 0.5);
        break;
    case 1:
        setButton("X", true);
        setStick(true, right ? 1 : 0, 0.5);
        break;
    case 5: //it can be done frame 4 but even the cpu messes up a lot
        setButton("X", false);
        setAnalogButton("L", 1);
        setStick(true, right ? 1 : 0, 0);
        break;
    case 7:
        setStick(true, 0.5, 0.5);
        setAnalogButton("L", 0);
        break;
    }
}

bool Ledgedash::hasEnded(const State& s) {
    return (s.me.actionState == ACTION::LANDING_SPECIAL) || ((s.frame - startFrame) > 15);
}
