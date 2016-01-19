#include "DI.h"
#include <iostream>
#include <cmath>

DI::DI() {
}

DI::~DI() {
}


void DI::execute(const State &s) {
    float speed = hypot(s.me.knockbackX, s.me.knockbackY);
    float kx = s.me.knockbackX;
    float ky = s.me.knockbackY;
    bool rev = false;
    if(kx < 0) {
        rev = true;
        kx = -kx;
    }
    float ka = atan2(ky, kx);
    if(ka < 0.5) { //attempt to tech the ground
        //TODO: HANDLE SLIDING OFF AFTER TECHING THE GROUND. Currently handles about up to 200% at the edge
        //Also, it is theoretically possible to tech other things, such as knee
        setStick(false, 0.5, 0); //ASDI to the ground
        setStick(true, rev ? 0 : 1, 0);
        //the tech must be inputted on the last two frames
        if(s.me.hitlagLeft <= 2) setAnalogButton("L", 1);
    } else {
        if(speed > 2.5) { //survival DI. TODO: determine best threshold
            if(s.me.hitlagLeft > 2) { //SDI to center stage
                if(s.me.y < 5 && s.me.y > 0) { //when close to the ground, do horizontal only
                    setStick(true, (s.me.x > 0) ? 0 : 1, 0.5 - 2 * SDI_DELTA + (s.frame % 2) * SDI_DELTA);
                } else {
                    if(s.frame % 2) setStick(true, s.me.x < 0, 0.5);
                    else setStick(true, 0.5, s.me.y < 0);
                }
            } else {
                //the axes for atan2 are swapped on purpose, as we need a perpendicular vector
                //vertical attacks are di'd "out" and horizontal "in"
                float angle = (kx > ky) ? atan2(kx, -ky) : atan2(-kx, ky);
                float dx = (rev ? (-1) : 1) * cos(angle);
                float dy = sin(angle);
                float coef = std::max(fabs(dx), fabs(dy));
                dx = (1 + dx / coef) / 2;
                dy = (1 + dy / coef) / 2;
                setStick(true, dx, dy);
            }
        } else {
            if(s.me.hitlagLeft > 2) { //SDI
                if(s.distanceToEdge(ME) > 30) //don't SDI yourself too far
                    setStick(true, rev ? 0 : 1, 0.5 - 2 * SDI_DELTA + (s.frame % 2) * SDI_DELTA);
            } else {
                setStick(true, rev ? 0 : 1, 0);
            }
        }
    }
}

bool DI::hasEnded(const State& s) {
    return (s.me.hitlagLeft < 1);
}
