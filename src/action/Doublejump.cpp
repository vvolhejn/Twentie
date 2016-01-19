#include "Doublejump.h"
#include <iostream>

Doublejump::Doublejump(u32 frame, float _di){
    startFrame = frame;
    di = _di;
}
Doublejump::~Doublejump(){
}


void Doublejump::execute(const State &s){
    setStick(true, di, 0.5);
    if(startFrame == s.frame) setButton("X", true);
    else setButton("X", false);
}

bool Doublejump::hasEnded(const State& s){
    return (s.frame - startFrame) > 1;
}
