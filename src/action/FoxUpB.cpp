#include "FoxUpB.h"
#include <iostream>
#include <cmath>

FoxUpB::FoxUpB(u32 frame) {
    startFrame = frame;
}
FoxUpB::~FoxUpB() {
}

inline void FoxUpB::aimTo(const State &s, float x, float y) {
    float dx = x - s.me.x;
    float dy = y - s.me.y;
    float angle = atan2(dy, dx);
    //std::cout << cos(angle) << " " << sin(angle) << std::endl;
    setStick(true, (cos(angle) + 1) / 2, (sin(angle) + 1) / 2);
}

void FoxUpB::execute(const State &s) {
    switch(s.frame - startFrame) {
    case 0:
        setStick(true, 0.5, 1);
        setButton("B", true);
        break;
    case 1:
        setButton("B", false);
        break;
    case 40: {
        aimTo(s, ((s.me.x > 0) ? 1 : (-1)) * (EDGE_X - 3), -5);
        //aimTo(s, ((s.me.x > 0) ? 1 : (-1)) * (EDGE_X + 5), 30);
        break;
    }
    case 50:
        setStick(true, 0.5, 0.5);
        break;
    }
    if(s.me.actionState == ACTION::SPECIAL_FALL) { //drift towards the stage
        setStick(true, s.me.x < 0, 0.5);
    }
}

bool FoxUpB::hasEnded(const State& s) {
    switch(s.me.actionState) {
    case FOX_UP_B_START_GROUND:
    case FOX_UP_B_START_AIR:
    case FOX_UP_B_GROUND:
    case FOX_UP_B_AIR:
    case FOX_UP_B_END:
    case SPECIAL_FALL:
        return false;
    default:
        break;
    }
    return ((s.frame - startFrame) > 10);
}
