#include "FoxSideB.h"
#include <iostream>

FoxSideB::FoxSideB(u32 frame, bool _right) {
    startFrame = frame;
    right = _right;
}
FoxSideB::~FoxSideB() {}


void FoxSideB::execute(const State &s) {
    switch(s.frame - startFrame) {
    case 0:
        setStick(true, right ? 1 : 0, 0.5);
        setButton("B", true);
        break;
    case 1:
        resetInputs();
        break;
    }
}

bool FoxSideB::hasEnded(const State& s) { //possibly better to find which action states mean illusion
    switch(s.players[ME].actionState) {
    case SIDE_B_START:
    case SIDE_B:
    case SIDE_B_END:
        return false;
    default:
        return true;
    }
}
